// JBS_Project


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		
		//attribute 값이 변경되었을 때 호출되는 함수들 바인딩
		OverlayWidgetController->BindCallbacksToDependencies();
}

	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class가 초기화 되지 않았습니다, BP_AuraHUD에 값을 넣어주세요."));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class가 초기화 되지 않았습니다, BP_AuraHUD에 값을 넣어주세요."));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);
	
	//컨트롤러 초기화
	const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
	OverlayWidgetController = GetOverlayWidgetController(WidgetControllerParams);
	
	OverlayWidget->SetWidgetController(OverlayWidgetController);
	
	OverlayWidgetController->BroadCastingInitialValues();
	
	Widget->AddToViewport();
}
