#include "SpawnerComponent.h"
#include "Components/ShapeComponent.h"
#include "SpawnablePoolComponent.h"
#include "SpawnerWorldSubSystem.h"
#include "SpawnRequest.h"

USpawnerComponent::USpawnerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void USpawnerComponent::InitializeComponent()
{
	Super::InitializeComponent();

	ensureAlwaysMsgf(GetOwner()->FindComponentByClass<USpawnablePoolComponent>(), TEXT("Actor (%s) with a SpawnerComponent needs"
		" to have the SpawnablePoolComponent as well."), *GetNameSafe(GetOwner()));
}

void USpawnerComponent::SpawnSpawnable(const TSubclassOf<USpawnable> Spawnable)
{
	if (const USpawnerWorldSubSystem* SWSS = GetWorld()->GetSubsystem<USpawnerWorldSubSystem>())
	{
		const FSpawnRequest Request(this, Spawnable);
		SWSS->Spawn(Request);
	}
}

void USpawnerComponent::PushSpawnRequest(const FSpawnRequest SpawnRequest) const
{
	if (const USpawnerWorldSubSystem* SWSS = GetWorld()->GetSubsystem<USpawnerWorldSubSystem>())
	{
		SWSS->Spawn(SpawnRequest);
	}
}

void USpawnerComponent::Spawn()
{
	if (const USpawnerWorldSubSystem* SWSS = GetWorld()->GetSubsystem<USpawnerWorldSubSystem>())
	{
		const FSpawnRequest Request(this);
		SWSS->Spawn(Request);
	}
}

void USpawnerComponent::AddSpawnableShape(const UShapeComponent* ShapeComponent)
{
	if (ensureAlways(IsValid(ShapeComponent)))
	{
		SpawnableShapes.AddUnique(ShapeComponent);
	}
}

bool USpawnerComponent::HasSpawnableShapes() const
{
	return SpawnableShapes.Num() > 0;
}

void USpawnerComponent::BeginPlay()
{
	Super::BeginPlay();
}
