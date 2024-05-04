#include "SpawnablePoolComponent.h"
#include "Spawnable.h"

USpawnablePoolComponent::USpawnablePoolComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USpawnablePoolComponent::AddSpawnableToPool(const TSubclassOf<USpawnable> Spawnable)
{
	SpawnablesPool.AddUnique(Spawnable);
}

TSubclassOf<USpawnable> USpawnablePoolComponent::GetRandomValidSpawnableFromPool() const
{
	TArray<TSubclassOf<USpawnable>, TInlineAllocator<10>> ValidSpawnables;
	for (const TSubclassOf<USpawnable>& Spawnable : SpawnablesPool)
	{
		if (Spawnable != nullptr)
		{
			ValidSpawnables.Add(Spawnable);
		}
	}

	if (ValidSpawnables.Num() > 0)
	{
		const int32 RandomIndex = FMath::RandRange(0, ValidSpawnables.Num() - 1);
		return ValidSpawnables[RandomIndex];
	}
	
	return nullptr;
}
