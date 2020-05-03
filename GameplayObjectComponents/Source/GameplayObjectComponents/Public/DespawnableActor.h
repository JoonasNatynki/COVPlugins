// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Despawnable.h"
#include "DespawnableActor.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogDespawnableActor, Log, All)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPLAYOBJECTCOMPONENTS_API UDespawnableActor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDespawnableActor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(Category = "Despawnable", BlueprintCallable)
		FDespawnableRecord GetActorState();

	UFUNCTION(Category = "Despawnable", BlueprintCallable)
		static void RestoreActorState(AActor* ActorToRestore, FDespawnableRecord Data);

	UFUNCTION(Category = "Despawnable", BlueprintCallable, meta = (WorldContext=WorldContextObject))
		static AActor* RespawnActorFromState(const UObject* WorldContextObject, FDespawnableRecord Data);
};
