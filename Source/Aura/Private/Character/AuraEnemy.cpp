// JBS_Project


#include "Character/AuraEnemy.h"

#include "Aura/Aura.h"

void AAuraEnemy::ActorDrawDebugSphere() const
{
	FVector ActorLocation = GetActorLocation();

	DrawDebugSphere(GetWorld(), ActorLocation, 50.0f, 12, FColor::Red);
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
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AAuraEnemy::HighlightActor()
{
	bHighlighted = true;

	GetMesh()->SetRenderCustomDepth(bHighlighted);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(bHighlighted);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnHighlightActor()
{
	bHighlighted = false;

	GetMesh()->SetRenderCustomDepth(bHighlighted);
	Weapon->SetRenderCustomDepth(bHighlighted);
}
