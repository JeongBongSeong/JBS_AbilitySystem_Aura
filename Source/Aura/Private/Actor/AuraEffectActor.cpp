// JBS_Project


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneComponent"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

//Target의 경우 적용될 타겟을 이야기함
void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	//타겟의 ASC를 가져옴
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	// block 체크
	if (TargetASC == nullptr) return;

	check(GameplayEffectClass);

	//컨텍스트 생성
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();

	EffectContextHandle.AddSourceObject(this);

	//스팩 핸들러 생성
	FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(
		GameplayEffectClass, 1.f, EffectContextHandle);

	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}
