// JBS_Project


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadCastingInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	float Health = AuraAttributeSet->GetHealth();
	float MaxHealth = AuraAttributeSet->GetMaxHealth();

	float Mana = AuraAttributeSet->GetMana();
	float MaxMana = AuraAttributeSet->GetMaxMana();

	OnHealthChanged.Broadcast(Health);
	OnMaxHealthChanged.Broadcast(MaxHealth);
	OnManaChanged.Broadcast(Mana);
	OnMaxManaChanged.Broadcast(MaxMana);
}

//변경된 attribute 값에 대한 함수 바인딩 작업
void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
}

//체력이 변경되었을 경우 브로드 캐스팅 하는 함수
void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

//최대 체력이 변경되었을 경우 브로드 캐스팅 하는 함수
void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

//마나가 변경되었을 경우 브로드 캐스팅 하는 함수
void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

//최대마나가 변경되었을 경우 브로드 캐스팅 하는 함수
void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
