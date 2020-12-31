#include "Inventory.h"
#include "InventoryItem.h"
#include <UnrealNetwork.h>
#include <Classes/Kismet/GameplayStatics.h>
#include "PropertyExchangableItemBase.h"

DEFINE_LOG_CATEGORY(LogInventory)

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	SetIsReplicated(true);
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty, FDefaultAllocator>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryComponent, Inventory);
}

void UInventoryComponent::TransferInventoryDataToObject(UObject* FromObject, UObject* ToObject) const
{
	ensure(IsValid(FromObject) && IsValid(ToObject));

	int32 PropertiesCopiedSuccessfully = 0;
	
	//	Go through each property in the class
	for (TFieldIterator<FProperty> Property_1(FromObject->GetClass()); Property_1; ++Property_1)
	{
		//	Now go through every property in the other object and see if there is a matching one
		for (TFieldIterator<FProperty> property_2(ToObject->GetClass()); property_2; ++property_2)
		{
			if(ShouldIgnoreBaseClassPropertyCopy(**Property_1))
			{
				continue;
			}
			
			//	Check that both have matching types and matching names
			const bool bNamesAndTypesMatch = Property_1->SameType(*property_2) && (Property_1->GetFName() == property_2->GetFName());

			if (bNamesAndTypesMatch)
			{
				UE_LOG(LogInventory, Verbose, TEXT("Copying (%s)(%s) property from (%s) to (%s)"), *Property_1->GetCPPType(), *Property_1->GetFName().ToString(), *GetNameSafe(FromObject), *GetNameSafe(ToObject));
				void* theData = Property_1->ContainerPtrToValuePtr<void>(FromObject);
				void* destinationData = property_2->ContainerPtrToValuePtr<void>(ToObject);
				Property_1->CopySingleValue(destinationData, theData);

				PropertiesCopiedSuccessfully++;
				
				break;
			}
		}
	}

	UE_LOG(LogInventory, Log, TEXT("Copied (%d) properties successfully from (%s) to (%s)."), PropertiesCopiedSuccessfully, *GetNameSafe(FromObject), *GetNameSafe(ToObject));
}

bool UInventoryComponent::ShouldIgnoreBaseClassPropertyCopy(const FProperty& Property1)
{
	for (TFieldIterator<FProperty> Property_1(APropertyExchangableItemBase::StaticClass()); Property_1; ++Property_1)
	{
		const bool bNamesAndTypesMatch = Property_1->SameType(&Property1) && (Property_1->GetFName() == Property1.GetFName());
		
		//	Ignore also uber graphs. TODO: How do to this better?
		const bool bIsUberGraph = Property1.GetCPPType() == FString("FPointerToUberGraphFrame");
		
		if(bNamesAndTypesMatch || bIsUberGraph)
		{
			return true;
		}
	}

	return false;
}

bool UInventoryComponent::AddItemToInventory(AActor* ItemActor)
{
	AActor* InventoryOwner = GetOwner();

	if (ensure(InventoryOwner->HasAuthority()))
	{
		ensure(IsValid(ItemActor));

		UE_LOG(LogInventory, Log, TEXT("Adding item (%s) to inventory on (%s)."), *GetNameSafe(ItemActor), *GetNameSafe(InventoryOwner));

		UInventoryItemComponent* InventoryItemComp = ItemActor->FindComponentByClass<UInventoryItemComponent>();

		if (IsValid(InventoryItemComp))
		{
			if (ensureMsgf(InventoryItemComp->CorrespondingActorClassToSpawn, TEXT("No [CorrespondingActorClassToSpawn] defined for the item (%s) being put into the inventory on actor (%s). The item could not be transferred to the inventory."), *GetNameSafe(ItemActor), *GetNameSafe(InventoryOwner)))
			{
				//	We spawn the actor deferred. This way we can initialize the actor and its properties properly before it Constructs or BeginPlays
				//	BEGIN SPAWN---------------------------------------------------------------------------------------------------------------------------------
				AActor* SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(InventoryItemComp->CorrespondingActorClassToSpawn, InventoryOwner->GetTransform());

				check(IsValid(SpawnedActor));

				//	Corresponding spawned actor must also have the inventory item component
				UInventoryItemComponent* SpawnedActorInventoryItemComp = SpawnedActor->FindComponentByClass<UInventoryItemComponent>();
				check(IsValid(SpawnedActorInventoryItemComp));
				//	Set the corresponding class to be who spawned it
				SpawnedActorInventoryItemComp->CorrespondingActorClassToSpawn = GetClass();
				//	Update the spawned item guid to match the original
				SpawnedActorInventoryItemComp->SetItemGUID(InventoryItemComp->GetItemGUID());

				UE_LOG(LogInventory, Verbose, TEXT("Corresponding actor (%s) spawned for item (%s). Transferring inventory data to the spawned object..."), *GetNameSafe(SpawnedActor), *GetNameSafe(ItemActor));

				TransferInventoryDataToObject(ItemActor, SpawnedActor);

				//	Ok now spawned actor can finalize spawning
				UGameplayStatics::FinishSpawningActor(SpawnedActor, SpawnedActor->GetTransform());
				//	END SPAWN---------------------------------------------------------------------------------------------------------------------------------

				//	Attach spawned actor to the inventory owner
				SpawnedActor->AttachToActor(InventoryOwner, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

				UE_LOG(LogInventory, Verbose, TEXT("Inventory data transferred to actor (%s)."), *GetNameSafe(SpawnedActor));

				Inventory.Add(SpawnedActor);
				OnRep_Inventory();
			}
			
			//	Maybe destroy the original item now?
			ItemActor->Destroy();

			return true;
		}
	}

	return false;
}

bool UInventoryComponent::RemoveItemFromInventory(AActor* Item)
{
	check(IsValid(Item));
	UInventoryItemComponent* ItemComp = Item->FindComponentByClass<UInventoryItemComponent>();

	if(IsValid(ItemComp))
	{
		return RemoveItemFromInventoryByGUID(ItemComp->GetItemGUID());
	}

	UE_LOG(LogInventory, Warning, TEXT("Item (%s) could not be removed from inventory on actor (%s). The item did not have an InventoryItemComponent"), *GetNameSafe(Item), *GetNameSafe(GetOwner()));
	
	return false;
}

bool UInventoryComponent::RemoveItemFromInventoryByGUID(const FGuid& ItemGUID)
{
	UInventoryItemComponent* FoundItem = nullptr;
	
	for(AActor* Item : Inventory)
	{
		UInventoryItemComponent* ItemComp = Item->FindComponentByClass<UInventoryItemComponent>();
		if(IsValid(ItemComp) && ItemComp->GetItemGUID() == ItemGUID)
		{
			//	Same item in inventory
			FoundItem = ItemComp;
			break;
		}
	}

	if(FoundItem)
	{
		Inventory.Remove(FoundItem->GetOwner());
		
		UE_LOG(LogInventory, Log, TEXT("Item (%s) with GUID (%s) removed from inventory on actor (%s)."), *GetNameSafe(FoundItem->GetOwner()), *ItemGUID.ToString(), *GetNameSafe(GetOwner()));

		//	TODO: Drop item and spawn collectible version
		
		return true;
	}
	else
	{
		UE_LOG(LogInventory, Log, TEXT("No item with GUID (%s) found in inventory of actor (%s)."), *ItemGUID.ToString(), *GetNameSafe(GetOwner()));
		return false;
	}
}

void UInventoryComponent::OnRep_Inventory()
{
	AActor* item = Inventory.Top();

	if (IsValid(item))
	{

		UE_LOG(LogInventory, Log, TEXT("OnRep_Inventory = (%s)"), *GetNameSafe(item));
		UInventoryItemComponent* inventoryItemComp = item->FindComponentByClass<UInventoryItemComponent>();
		OnItemAdded.Broadcast(inventoryItemComp);
	}
}
