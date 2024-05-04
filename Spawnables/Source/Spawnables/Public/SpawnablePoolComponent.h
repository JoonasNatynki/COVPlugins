// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpawnablePoolComponent.generated.h"

class USpawnable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class USpawnablePoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnablePoolComponent();

	UFUNCTION(Category = "Spawnable", BlueprintCallable)
	void AddSpawnableToPool(const TSubclassOf<USpawnable> Spawnable);

	UFUNCTION(Category = "Spawnable", BlueprintCallable, BlueprintPure)
	TSubclassOf<USpawnable> GetRandomValidSpawnableFromPool() const;

	UPROPERTY(Category = "Spawnable", EditAnywhere)
	TArray<TSubclassOf<USpawnable>> SpawnablesPool;
};
