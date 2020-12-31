// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PropertyExchangableItemBase.h"
#include "GameFramework/Actor.h"
#include "CollectibleItemBase.generated.h"

UCLASS()
class INVENTORYANDITEMS_API ACollectibleItemBase : public APropertyExchangableItemBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectibleItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
