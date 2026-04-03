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

void AAuraEnemy::HighlightActor()
{
	bHighlighted = true;

	if (UPrimitiveComponent* Mesh = GetMesh())
	{
		Mesh->SetRenderCustomDepth(bHighlighted);
		Mesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

		if (UPrimitiveComponent* child = Cast<UPrimitiveComponent>(Mesh->GetChildComponent(0)))
		{
			child->SetRenderCustomDepth(bHighlighted);
			child->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
		}
	}
}

void AAuraEnemy::UnHighlightActor()
{
	bHighlighted = false;

	if (UPrimitiveComponent* Mesh = GetMesh())
	{
		Mesh->SetRenderCustomDepth(bHighlighted);

		if (UPrimitiveComponent* child = Cast<UPrimitiveComponent>(Mesh->GetChildComponent(0)))
		{
			child->SetRenderCustomDepth(bHighlighted);
		}
	}
}
