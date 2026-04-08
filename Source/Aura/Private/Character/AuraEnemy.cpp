// JBS_Project


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"

void AAuraEnemy::ActorDrawDebugSphere() const
{
	FVector ActorLocation = GetActorLocation();

	DrawDebugSphere(GetWorld(), ActorLocation, 50.0f, 12, FColor::Red);
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
}

void AAuraEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// if (bHighlighted)
	// {
	// 	ActorDrawDebugSphere();
	// }
}

AAuraEnemy::AAuraEnemy()
{
	//콜리전 block 세팅
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	//AI 몬스터 일 예정이기 때문에 컴파일을 최소한의 기능만 사용가능 하도록 설정한다.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

//하이라이트 ON
void AAuraEnemy::HighlightActor()
{
	bHighlighted = true;

	GetMesh()->SetRenderCustomDepth(bHighlighted);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(bHighlighted);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

//하이라이트 OFF
void AAuraEnemy::UnHighlightActor()
{
	bHighlighted = false;

	GetMesh()->SetRenderCustomDepth(bHighlighted);
	Weapon->SetRenderCustomDepth(bHighlighted);
}
