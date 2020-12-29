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

void UInventoryComponent::TransferInventoryDataToObject(UObject* FromObject, UObject* ToObject) const
{
	ensure(IsValid(FromObject) && IsValid(ToObject));

	//	Go through each property in the class
	for (TFieldIterator<FProperty> property_1(FromObject->GetClass()); property_1; ++property_1)
	{
		//	Now go through every property in the other object and see if there is a matching one
		for (TFieldIterator<FProperty> property_2(ToObject->GetClass()); property_2; ++property_2)
		{
			//	Check that both have matching types and matching names
			const bool bNamesAndTypesMatch = property_1->SameType(*property_2) && (property_1->GetFName() == property_2->GetFName());

			if (bNamesAndTypesMatch)
			{
				UE_LOG(LogInventory, Verbose, TEXT("Copying (%s)(%s) property from (%s) to (%s)"), *property_1->GetCPPType(), *property_1->GetFName().ToString(), *GetNameSafe(FromObject), *GetNameSafe(ToObject));
				void* theData = property_1->ContainerPtrToValuePtr<void>(FromObject);
				void* destinationData = property_2->ContainerPtrToValuePtr<void>(ToObject);
				property_1->CopySingleValue(destinationData, theData);

				break;
			}
		}
	}
}

bool UInventoryComponent::AddItem(AActor* ItemActor)
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

bool UInventoryComponent::RemoveItem(AActor* Item)
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