// JBS_Project


#include "Character/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

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
