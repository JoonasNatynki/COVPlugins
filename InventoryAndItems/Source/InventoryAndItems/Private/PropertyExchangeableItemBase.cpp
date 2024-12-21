#include "PropertyExchangeableItemBase.h"
#include "InventoryItem.h"

APropertyExchangeableItemBase::APropertyExchangeableItemBase()
{
	PrimaryActorTick.bCanEverTick = false;

	InventoryItem = CreateDefaultSubobject<UInventoryItemComponent>(FName("InventoryItemComponent"));
}

void APropertyExchangeableItemBase::BeginPlay()
{
	Super::BeginPlay();
}