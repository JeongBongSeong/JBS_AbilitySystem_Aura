// JBS_Project


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"
#include "DrawDebugHelpers.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	
	//단순한 충돌 체크
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	
	//블락된게 없다면 리턴
	if (!CursorHit.bBlockingHit) return;
	
	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();
	
	/**
	 * 커서 추적
	 * 
	 *	A. LastActor is null && ThisActor is null
	 *		- 아무일도 하지 않음
	 * B. LastActor is null && ThisActor is valid
	 *		- Highlight ThisActor
	 * C. LastActor is valid && ThisActor is null
	 * 		- UnHighlight LastActor
	 * D. Both Actors are valid, but LastActor != ThisActor
	 * 		- UnHighlight LastActor
	 * 		- Highlight ThisActor
	 * E. Both Actors are valid, but are the same actor
	 * 		- 아무 일도 하지 않음
	 */
	
	if (ThisActor != LastActor)
	{
		// Cast B, C
		if (ThisActor == nullptr && LastActor != nullptr)
		{
			LastActor->UnHighlightActor();
		}
		else if (ThisActor != nullptr && LastActor == nullptr)
		{
			ThisActor->HighlightActor();
		}
		else if (ThisActor != nullptr && LastActor != nullptr)
		{
			LastActor->UnHighlightActor();
			ThisActor->HighlightActor();
		}
	}
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//아우라 컨텍스트 확인 어썰트

	check(AuraContext);

	//서브시스템(관리자)를 불러와서 향상된 UEnhancedInputLocalPlayerSubsystem을 가져오는 것(현재 플레이어를 통해)
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	Subsystem->AddMappingContext(AuraContext, 0);

	//마우스 커서를 숨기지 않음
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	//Move함수를 바인드하고 누르고있을 때 실행되도록한다.
	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	//폰을 가져오고, 이동을 추가한다.
	if (APawn* ControllerPawn = GetPawn<APawn>())
	{
		ControllerPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControllerPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}