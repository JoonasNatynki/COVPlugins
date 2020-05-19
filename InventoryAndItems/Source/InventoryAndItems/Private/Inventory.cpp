#include "Inventory.h"
#include "InventoryItem.h"
#include <UnrealNetwork.h>
#include <Classes/Kismet/GameplayStatics.h>

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

void UInventoryComponent::TransferInventoryDataToObject(UObject* fromObject, UObject* toObject) const
{
	ensure(IsValid(fromObject) && IsValid(toObject));

	//	Go through each property in the class and look for a metatag with the INVENTORYPROPERTY
	for (TFieldIterator<FProperty> property_1(fromObject->GetClass()); property_1; ++property_1)
	{
		const FName metaTag(INVENTORYPROPERTY);
		const bool bHasMetaTag_1 = property_1->HasMetaData(metaTag);

		//	Only look into properties that have the metadata tag. These items want these properties to pass over to the item as it is put into - or taken out - of the inventory.
		if(bHasMetaTag_1)
		{
			//	Now go through every property in the other object and see if there is a matching one
			for (TFieldIterator<FProperty> property_2(toObject->GetClass()); property_2; ++property_2)
			{
				const bool bHasMetaTag_2 = property_2->HasMetaData(metaTag);

				if (bHasMetaTag_2 && (property_1->SameType(*property_1)) && (property_1->GetFName() == property_2->GetFName()))
				{
					UE_LOG(LogInventory, Log, TEXT("Copying (%s)(%s) property from (%s) to (%s)"), *property_1->GetCPPType(), *property_1->GetFName().ToString(), *GetNameSafe(fromObject), *GetNameSafe(toObject));
					void* theData = property_1->ContainerPtrToValuePtr<void>(fromObject);
					void* destinationData = property_2->ContainerPtrToValuePtr<void>(toObject);
					property_1->CopySingleValue(destinationData, theData);

					break;
				}
			}
		}
	}
}

bool UInventoryComponent::AddItem(AActor* itemActor)
{
	if (ensure(GetOwner()->HasAuthority()))
	{
		ensure(IsValid(itemActor));

		UE_LOG(LogInventory, Log, TEXT("Adding item (%s) to inventory on (%s)."), *GetNameSafe(itemActor), *GetNameSafe(GetOwner()));

		UInventoryItemComponent* inventoryItemComp = itemActor->FindComponentByClass<UInventoryItemComponent>();

		if (IsValid(inventoryItemComp))
		{
			if (ensureMsgf(inventoryItemComp->CorrespondingActorClassToSpawn, TEXT("No corresponding item class defined for the inventory item. Is this intended?")))
			{
				//	We spawn the actor deferred. This way we can initialize the actor and its properties properly before it Constructs or BeginPlays
				//	BEGIN SPAWN---------------------------------------------------------------------------------------------------------------------------------
				AActor* spawnedActor = GetWorld()->SpawnActorDeferred<AActor>(inventoryItemComp->CorrespondingActorClassToSpawn, GetOwner()->GetTransform());

				check(IsValid(spawnedActor));

				//	Corresponding spawned actor must also have the inventory item component
				UInventoryItemComponent* spawnedActorInventoryItemComp = spawnedActor->FindComponentByClass<UInventoryItemComponent>();
				check(IsValid(spawnedActorInventoryItemComp));
				//	Set the corresponding class to be who spawned it
				spawnedActorInventoryItemComp->CorrespondingActorClassToSpawn = GetClass();
				//	Update the spawned item guid to match the original
				spawnedActorInventoryItemComp->SetItemGUID(inventoryItemComp->GetItemGUID());

				UE_LOG(LogInventory, Verbose, TEXT("Corresponding actor (%s) spawned for item (%s). Transferring inventory data to the spawned object..."), *GetNameSafe(spawnedActor), *GetNameSafe(itemActor));

				TransferInventoryDataToObject(itemActor, spawnedActor);

				//	Ok now spawned actor can finalize spawning
				UGameplayStatics::FinishSpawningActor(spawnedActor, spawnedActor->GetTransform());
				//	END SPAWN---------------------------------------------------------------------------------------------------------------------------------

				//	Attach spawned actor to the inventory owner
				spawnedActor->AttachToActor(GetOwner(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);

				UE_LOG(LogInventory, Verbose, TEXT("Inventory data transferred to actor (%s)."), *GetNameSafe(spawnedActor));

				Inventory.Add(spawnedActor);
				OnRep_Inventory();
			}

			//	Maybe destroy the original item now?
			itemActor->Destroy();

			return true;
		}
	}

	return false;
}

bool UInventoryComponent::RemoveItem(AActor* item)
{
	return false;
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