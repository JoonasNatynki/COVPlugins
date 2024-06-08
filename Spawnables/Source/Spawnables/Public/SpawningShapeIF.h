#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/BoxComponent.h"
#include "UObject/Interface.h"
#include "SpawningShapeIF.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USpawningShapeIF : public UInterface
{
	GENERATED_BODY()
};

USTRUCT()
struct FConsumedSpace
{
	GENERATED_BODY()

	FConsumedSpace(){};
	explicit FConsumedSpace(const FTransform& Trans, const FBox& Box)
	{
		Transform = Trans;
		ConsumedBox = Box;
	}
	
	FTransform Transform;
	FBox ConsumedBox;
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

	// Consumes the spawn space within the shape volume so that the space can't be spawned for something else
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	const bool ConsumeSpawnSpace(const FTransform& SpawnTransformInSpace, const FBox& SpawnBB);
	const bool ConsumeSpawnSpace_Implementation(const FTransform& SpawnTransformInSpace, const FBox& SpawnBB);
	FTransform FindPlacementForBox(const UBoxComponent* BoxComponent, const FBox& BoxToFit) const;

	TArray<FConsumedSpace> ConsumedSpaces;
};
