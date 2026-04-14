// JBS_Project


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	if (ensure(InWidgetController != nullptr))
	{
		WidgetController = InWidgetController;
		WidgetConterollerSet();
	}
}
