// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Inventory.h"
#include "CollectibleExample.generated.h"

UCLASS()
class INVENTORYANDITEMS_API ACollectibleExample : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectibleExample();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collectible")
		//	All actors that can be put into an inventory will need to have the inventory item component
		class UInventoryItemComponent* InventoryItem;

	//	This is an example of a property that will automatically be passed on between collectible/inventory version(s) of the same item
	UPROPERTY(BlueprintReadOnly, Category = "Gun", meta = (INVENTORYPROPERTY))
		int32 Ammo = -1;	//	Will carry over to the other actor version
	//	This is an example of a property that will automatically be passed on between collectible/inventory version(s) of the same item
	UPROPERTY(BlueprintReadOnly, Category = "Gun", meta = (INVENTORYPROPERTY))
		float Damage = 0.0f;	//	Will carry over to the other actor version
};
