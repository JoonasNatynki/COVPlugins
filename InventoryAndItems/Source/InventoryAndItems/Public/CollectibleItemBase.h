// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectibleItemBase.generated.h"

UCLASS()
class INVENTORYANDITEMS_API ACollectibleItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectibleItemBase();

	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collectible")
	//	All actors that can be put into an inventory will need to have the inventory item component
	class UInventoryItemComponent* InventoryItem;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
