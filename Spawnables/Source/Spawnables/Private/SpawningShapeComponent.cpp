#include "SpawningBoxShapeComponent.h"
#include "SpawnerComponent.h"

USpawningBoxShapeComponent::USpawningBoxShapeComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	SetGenerateOverlapEvents(false);
}

void USpawningBoxShapeComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (USpawnerComponent* SpawnComp = GetOwner()->FindComponentByClass<USpawnerComponent>())
	{
		SpawnComp->AddSpawnableShape(this);
	}
}
