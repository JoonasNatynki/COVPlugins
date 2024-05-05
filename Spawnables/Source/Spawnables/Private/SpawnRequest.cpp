#include "SpawnRequest.h"
#include "SpawnerComponent.h"
#include "Spawnable.h"
#include "SpawnablePoolComponent.h"
#include "SpawnerWorldSubSystem.h"

DEFINE_LOG_CATEGORY(LogSpawnRequest)

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

	if (!ensureAlways(IsValid(Spawnable)))
	{
		return;
	}

	bTryToAdjustForEncroachingGeometry = SpawnerComponent->bTryToAdjustForEncroachingGeometry;
	Instigator = SpawnerComponent->GetOwner();

	if (SpawnerComponent->bUseSpawnableShapes)
	{
		if (!SpawnerComponent->HasSpawnableShapes())
		{
			UE_LOG(LogSpawnRequest, Warning, TEXT("Spawner on actor (%s) was set to use spawnable shapes, but it"
				 " did not have any. Did you forget to add spawnable shapes?"),
				 *GetNameSafe(SpawnerComponent->GetOwner()));

			SpawnTransform = SpawnerComponent->GetComponentTransform();
		}
		else if (const ISpawningShapeIF* RandShape = USpawnerWorldSubSystem::GetRandomSpawningShapeComponentOnActor(
			SpawnerComponent->GetOwner(),
			Spawnable->GetDefaultObject<USpawnable>()))
		{
			const FVector RandPointInShape =
				ISpawningShapeIF::Execute_GetRandomPointInShapeComponent(
					CastChecked<UObject>(RandShape),
					SpawnerComponent->bTryFindSurfaceToPlace);
			
			SpawnTransform.SetLocation(RandPointInShape);

			FVector Origin;
			FVector BoxExtent;
			SpawnerComponent->GetOwner()->GetActorBounds(true, Origin, BoxExtent, true);
			const FBox SpawnBB(Origin - BoxExtent, Origin + BoxExtent);
			// Consume that point in the shape so that it doesn't give other spawn points within that space
			ISpawningShapeIF::Execute_ConsumeSpawnSpace(
					CastChecked<UObject>(RandShape),
					SpawnTransform,
					SpawnBB
					);
		}
	}
	else
	{
		SpawnTransform = SpawnerComponent->GetComponentTransform();
	}
}

const FString FSpawnRequest::ToString() const
{
	const FString ReturnString = GetNameSafe(Spawnable);
	return ReturnString;
}

UObject* FSpawnRequest::GetInstigator() const
{
	return Instigator.Get();
}
