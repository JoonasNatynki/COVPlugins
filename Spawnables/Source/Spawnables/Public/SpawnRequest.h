#pragma once

#include "Runtime/Engine/Classes/Engine/World.h"
#include "SpawnRequest.generated.h"

class AActor;
class USpawnerComponent;
class USpawnable;

DECLARE_LOG_CATEGORY_EXTERN(LogSpawnRequest, Log, All);

USTRUCT(Blueprintable)
struct FSpawnRequest
{
	GENERATED_BODY()

	FSpawnRequest() {}
	explicit FSpawnRequest(
		const TSubclassOf<USpawnable>& InSpawnable,
		const FTransform& InSpawnTransform,
		const FActorSpawnParameters& InSpawnParameters = FActorSpawnParameters(),
		const bool InbRecordSpawnData = true,
		const bool InbTryToAdjustForEncroachingGeometry = false
		);
	explicit FSpawnRequest(const USpawnerComponent* SpawnerComponent, const TSubclassOf<USpawnable> InSpawnable);
	explicit FSpawnRequest(const USpawnerComponent* SpawnerComponent);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient)
	TSubclassOf<USpawnable> Spawnable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient)
	FTransform SpawnTransform;
	
	FActorSpawnParameters SpawnParameters;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient)
	bool bRecordSpawnData = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient)
	bool bTryToAdjustForEncroachingGeometry = false;

	const FString ToString() const;

	UObject* GetInstigator() const;
	
private:
	void InitializeFromSpawner(const USpawnerComponent* SpawnerComponent);
	
	TWeakObjectPtr<UObject> Instigator = nullptr;
};