#pragma once

#include "GameplayTagContainer.h"
#include "SpawnableProperty.generated.h"

UCLASS(Abstract)
class USpawnableProperty : public UObject
{
	GENERATED_BODY()
};

// Gameplay tag requirements for various spawners and their components
UCLASS(DefaultToInstanced, EditInlineNew)
class USpawnerGameplayTagRequirement : public USpawnableProperty
{
	GENERATED_BODY()

public:
	// Needs to pass in order for the spawn to be allowed
	UPROPERTY(EditAnywhere)
	FGameplayTagQuery TagQuery;
};

