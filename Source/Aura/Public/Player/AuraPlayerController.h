// JBS_Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

struct FInputActionValue;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;
	
	//wasd 
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	
	//수정되지 않도록 const하고,데이터를 복사해서 가져오면 메모리 낭비가 생기고 낭비를 줄이기위해 주소값만 받아온다.
	//struct의 경우 이것을 미리 구조체라는 것을 알려주는 전방선언(Forward Declaration)
	void Move(const FInputActionValue& InputActionValue);
};
