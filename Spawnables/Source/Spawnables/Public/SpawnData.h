#pragma once

#include "SpawnData.generated.h"

class USpawnerWorldSubSystem;
class AActor;

USTRUCT()
struct FSpawnData
{
	GENERATED_BODY()

	FSpawnData(){};
	
	friend USpawnerWorldSubSystem;
	
public:
	AActor* GetSpawnedActor() const;
	
private:
	TWeakObjectPtr<AActor> SpawnedActor;
	TSubclassOf<AActor> SpawnedActorClass;

	bool IsValid() const;
	const FString ToString() const;

	operator bool() const
	{
		return IsValid();
	}
};
