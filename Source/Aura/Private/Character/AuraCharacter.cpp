// JBS_Project


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->bOrientRotationToMovement = true;
	Movement->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	Movement->bConstrainToPlane = true;
	Movement->bSnapToPlaneAtStart = true;

	//몸통 방향을 고정하지 않음
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//바닥을 설정해줘서 bSnapToPlaneAtStart
	//Movement->SetPlaneConstraintNormal(FVector(0.0f, 0.0f, 1.0f));
}

// 서버용 빙의 시점
void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//서버에 대한 ASC 정보를 캐싱하고 초기화 한다.
	InitAbilityActorInfo();

	//HUD에서 Overlay를 초기화 하는 부분
	InitOverlay();
}

//클라이언트용 빙의시점
void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//클라이언트에 대한 ASC정보를 캐싱하고 초기화 한다.
	InitAbilityActorInfo();

	//HUD에서 Overlay를 초기화 하는 부분
	//InitOverlay();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState)

	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();

	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);
}

void AAuraCharacter::InitOverlay()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController());
	
	if (AuraPlayerState && AuraPlayerController)
	{
		if (AAuraHUD* HUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			HUD->InitOverlay(AuraPlayerController,AuraPlayerState,AbilitySystemComponent,AttributeSet);
		}
	}
}
