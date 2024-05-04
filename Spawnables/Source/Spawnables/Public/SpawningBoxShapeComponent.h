#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SpawningShapeIF.h"
#include "Components/BoxComponent.h"
#include "SpawningBoxShapeComponent.generated.h"

// A spawning shape component that is used as a volume of space where something can spawn in
UCLASS(ClassGroup="Collision", hidecategories=(Object,LOD,Lighting,TextureStreaming, Navigation, HLOD, Rendering, Physics, PathTracing, Collision, Cooking, ComponentTick, Sockets), editinlinenew, meta=(DisplayName="Spawning Box Shape", BlueprintSpawnableComponent), MinimalAPI)
class USpawningBoxShapeComponent : public UBoxComponent, public ISpawningShapeIF
{
	GENERATED_BODY()

public:
	USpawningBoxShapeComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void InitializeComponent() override;

	// Spawn tags that can limit the types of spawns that can happen into this shape
	UPROPERTY(Category = "Spawning", EditAnywhere)
	FGameplayTagContainer SpawnableTags;
};
