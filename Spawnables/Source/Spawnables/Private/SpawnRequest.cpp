#include "SpawnRequest.h"
#include "SpawnerComponent.h"
#include "Spawnable.h"
#include "SpawnablePoolComponent.h"
#include "SpawnerWorldSubSystem.h"

FSpawnRequest::FSpawnRequest(
	const TSubclassOf<USpawnable>& InSpawnable,
	const FTransform& InSpawnTransform,
	const FActorSpawnParameters& InSpawnParameters,
	const bool InbRecordSpawnData,
	const bool InbTryToAdjustForEncroachingGeometry)
{
	Spawnable = InSpawnable;
	SpawnTransform = InSpawnTransform;
	SpawnParameters = InSpawnParameters;
	bRecordSpawnData = InbRecordSpawnData;
	bTryToAdjustForEncroachingGeometry = InbTryToAdjustForEncroachingGeometry;
}

FSpawnRequest::FSpawnRequest(const USpawnerComponent* SpawnerComponent, const TSubclassOf<USpawnable> InSpawnable)
{
	if (!ensureAlways(IsValid(SpawnerComponent)) || !ensureAlways(IsValid(InSpawnable)))
	{
		return;
	}

	Spawnable = InSpawnable;
	InitializeFromSpawner(SpawnerComponent);
}

FSpawnRequest::FSpawnRequest(const USpawnerComponent* SpawnerComponent)
{
	if (!ensureAlways(IsValid(SpawnerComponent)))
	{
		return;
	}

	if (const USpawnablePoolComponent* SpawnablePoolComponent =
		SpawnerComponent->GetOwner()->FindComponentByClass<USpawnablePoolComponent>())
	{
		Spawnable = SpawnablePoolComponent->GetRandomValidSpawnableFromPool();
	}
	else
	{
		ensureAlwaysMsgf(false, TEXT("Could not resolve a spawnable for spawn request."));
		return;
	}

	InitializeFromSpawner(SpawnerComponent);
}

void FSpawnRequest::InitializeFromSpawner(const USpawnerComponent* SpawnerComponent)
{
	if (!ensureAlways(IsValid(SpawnerComponent)))
	{
		return;
	}

	bTryToAdjustForEncroachingGeometry = SpawnerComponent->bTryToAdjustForEncroachingGeometry;
	Instigator = SpawnerComponent->GetOwner();

	if (SpawnerComponent->bUseSpawnableShapes && SpawnerComponent->HasSpawnableShapes())
	{
		const USpawningBoxShapeComponent* RandShape = USpawnerWorldSubSystem::GetRandomSpawningShapeComponentOnActor(
			SpawnerComponent->GetOwner(),
			Spawnable->GetDefaultObject<USpawnable>());

		if (IsValid(RandShape))
		{
			const FVector RandPointInShape = RandShape->Execute_GetRandomPointInShapeComponent(RandShape, SpawnerComponent->bTryFindSurfaceToPlace);
			SpawnTransform.SetLocation(RandPointInShape);
		}
	}
	else
	{
		SpawnTransform = SpawnerComponent->GetComponentTransform();
	}
}


const FString FSpawnRequest::ToString() const
{
	FString ReturnString = GetNameSafe(Spawnable);
	return ReturnString;
}

UObject* FSpawnRequest::GetInstigator() const
{
	return Instigator.Get();
}
