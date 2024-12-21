#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PropertyExchangeableItemBase.generated.h"

class UInventoryItemComponent;

UCLASS()
class INVENTORYANDITEMS_API APropertyExchangeableItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	APropertyExchangeableItemBase();

	//	All actors that can be put into an inventory will need to have the inventory item component
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collectible")
	UInventoryItemComponent* InventoryItem;

protected:
	virtual void BeginPlay() override;

};
