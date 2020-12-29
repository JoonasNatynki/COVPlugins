// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Inventory.h"
#include "InventoryItemBase.h"

#include "InventoryItemExample.generated.h"

UCLASS()
class INVENTORYANDITEMS_API AInventoryItemExample : public AInventoryItemBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryItemExample();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//	This is an example of a property that will automatically be passed on between collectible/inventory version(s) of the same item
	UPROPERTY(BlueprintReadOnly, Category = "Gun")
		int32 Ammo = -1;	//	Will carry over to the other actor version
	//	This is an example of a property that will automatically be passed on between collectible/inventory version(s) of the same item
	UPROPERTY(BlueprintReadOnly, Category = "Gun")
		float Damage = 0.0f;	//	Will carry over to the other actor version
};
