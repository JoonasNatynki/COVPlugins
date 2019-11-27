// Fill out your copyright notice in the Description page of Project Settings.

#include "CollectibleExample.h"
#include "InventoryItem.h"

// Sets default values
ACollectibleExample::ACollectibleExample()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//	Create the inventory item component
	InventoryItem = CreateDefaultSubobject<UInventoryItemComponent>(FName("InventoryItemComponent"));
}

// Called when the game starts or when spawned
void ACollectibleExample::BeginPlay()
{
	Super::BeginPlay();

	//	Let's set the ammo to something
	Ammo = 1;
}

// Called every frame
void ACollectibleExample::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

