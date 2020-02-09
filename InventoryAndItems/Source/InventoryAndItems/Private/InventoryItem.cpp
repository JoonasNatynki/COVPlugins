#include "InventoryItem.h"
#include <UnrealNetwork.h>

DEFINE_LOG_CATEGORY(LogInventoryItem)

UInventoryItemComponent::UInventoryItemComponent()
{
	SetIsReplicatedByDefault(true);
}

void UInventoryItemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty, FDefaultAllocator>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryItemComponent, ItemGUID);
}

void UInventoryItemComponent::OnRep_ItemGUID()
{
	UE_LOG(LogInventoryItem, Log, TEXT("OnRep_ItemGUID = (%s)"), *ItemGUID.ToString());
}

void UInventoryItemComponent::SetItemGUID(FGuid itemGuid)
{
	ensure(GetOwner()->HasAuthority());
	ItemGUID = itemGuid;
	UE_LOG(LogInventoryItem, Verbose, TEXT("ItemGUID set to (%s) on (%s)."), *ItemGUID.ToString(), *GetNameSafe(GetOwner()));
}

void UInventoryItemComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!ItemGUID.IsValid() && GetOwner()->HasAuthority())
	{
		ItemGUID = FGuid::NewGuid();
	}
}
