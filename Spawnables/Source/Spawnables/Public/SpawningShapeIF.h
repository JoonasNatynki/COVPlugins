#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "SpawningShapeIF.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USpawningShapeIF : public UInterface
{
	GENERATED_BODY()
};

class ISpawningShapeIF
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual const FGameplayTagContainer& GetSpawnableTags() const = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	const FVector GetRandomPointInShapeComponent(const bool bTryFindSurface = false) const;
	const FVector GetRandomPointInShapeComponent_Implementation(const bool bTryFindSurface = false) const;
};
