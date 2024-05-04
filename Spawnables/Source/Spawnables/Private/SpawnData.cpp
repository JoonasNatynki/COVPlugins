#include "SpawnData.h"

AActor* FSpawnData::GetSpawnedActor() const
{
	return SpawnedActor.Get();
}

bool FSpawnData::IsValid() const
{
	return SpawnedActorClass != nullptr;
}

const FString FSpawnData::ToString() const
{
	FString ReturnString = GetNameSafe(SpawnedActorClass);

	return ReturnString;
}
