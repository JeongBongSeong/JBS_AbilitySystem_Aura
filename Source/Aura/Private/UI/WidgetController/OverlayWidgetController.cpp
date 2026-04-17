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
