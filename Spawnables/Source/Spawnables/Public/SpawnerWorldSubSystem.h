#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SpawnData.h"
#include "SpawningBoxShapeComponent.h"
#include "SpawnerWorldSubSystem.generated.h"

class USpawnable;
struct FSpawnData;
struct FSpawnRequest;

DECLARE_LOG_CATEGORY_EXTERN(LogSpawnerWorldSubSystem, Log, All)

UCLASS()
class USpawnerWorldSubSystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	bool Spawn(const FSpawnRequest& SpawnRequest) const;

	// Get random spawning shape and optionally make sure it is valid for the spawnable
	static USpawningBoxShapeComponent* GetRandomSpawningShapeComponentOnActor(
		const AActor* ActorWithSpawningShapes,
		const USpawnable* SpawnableContext = nullptr);
	
private:
	const FSpawnData ProcessSpawnRequest(const FSpawnRequest& SpawnRequest) const;
	static void SpawnedActorLocationAdjustments_Internal(const FSpawnRequest& Request, AActor* SpawnedActor);
};

static TArray<FSpawnData> SpawnDatas;
