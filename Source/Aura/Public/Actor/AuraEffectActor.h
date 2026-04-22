// JBS_Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()

public:
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;

	/**
	 * 지정된 대상 액터에게 게임플레이 이펙트(GE)를 적용합니다.
	 * 대상의 ASC(Ability System Component)를 찾아 이펙트 스펙을 생성하고 즉시 적용합니다.
	 * @param Target 이펙트가 적용될 대상 액터 (Target의 ASC를 내부적으로 찾습니다)
	 * @param GameplayEffectClass 대상에게 적용할 게임플레이 이펙트 클래스 (설계도)
	 */
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UPROPERTY(EditAnywhere, Category="Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
};
