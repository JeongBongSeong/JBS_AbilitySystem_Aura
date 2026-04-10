// JBS_Project


#include "Actor/AuraPotionEffectActor.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AAuraPotionEffectActor::AAuraPotionEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SceneRoot=CreateDefaultSubobject<USceneComponent>("SceneRoot");
	SetRootComponent(SceneRoot);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(SceneRoot);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(SceneRoot);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Pickups/Potions/SM_PotionBottle.SM_PotionBottle'"));
	
	if (MeshAsset.Succeeded())
	{
		Mesh->SetStaticMesh(MeshAsset.Object);
		
		Mesh->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
		
		Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 75.0f));
	}
}

void AAuraPotionEffectActor::BeginPlay()
{
	Super::BeginPlay();

	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraPotionEffectActor::OnOverlap);
}

void AAuraPotionEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* ASCInterfae = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(ASCInterfae->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		UAuraAttributeSet* MutAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
		
		MutAttributeSet->SetHealth(MutAttributeSet->GetHealth()+20.0f);
		
		Destroy();
	}
}

void AAuraPotionEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
