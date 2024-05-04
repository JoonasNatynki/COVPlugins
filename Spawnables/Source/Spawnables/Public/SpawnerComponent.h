#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpawnerComponent.generated.h"

struct FSpawnRequest;
class USpawnable;

// Spawner component that is capable of spawning many things
UCLASS( ClassGroup=(Spawning), meta=(BlueprintSpawnableComponent))
class USpawnerComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	USpawnerComponent();
	virtual void InitializeComponent() override;

	// If true will try to use the spawnable shapes as spawn locations
	UPROPERTY(Category = "Spawner", EditAnywhere)
	bool bUseSpawnableShapes = true;

	// If true, will try to find a surface beneath th spawn point to place the spawnable onto
	UPROPERTY(Category = "Spawner", EditAnywhere)
	bool bTryFindSurfaceToPlace = true;
	
	// If encroaching on geometry, try to adjust to a free location from it
	UPROPERTY(Category = "Spawner", EditAnywhere)
	bool bTryToAdjustForEncroachingGeometry = true;

	UFUNCTION(Category = "Spawner", BlueprintCallable)
	void SpawnSpawnable(const TSubclassOf<USpawnable> Spawnable);
	
	UFUNCTION(Category = "Spawner", BlueprintCallable)
	void PushSpawnRequest(const FSpawnRequest SpawnRequest) const;

	UFUNCTION(Category = "Spawner", BlueprintCallable)
	void Spawn();

	// Use this to add custom shape components for the shape spawning
	UFUNCTION(Category = "Spawner", BlueprintCallable)
	void AddSpawnableShape(const UShapeComponent* ShapeComponent);
	
	bool HasSpawnableShapes() const;

protected:
	virtual void BeginPlay() override;

	// The shape components things can spawn into
	UPROPERTY()
	TArray<TObjectPtr<const UShapeComponent>> SpawnableShapes;
};
