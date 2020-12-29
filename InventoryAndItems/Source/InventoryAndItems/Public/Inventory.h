#pragma once

#include "Inventory.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogInventory, Log, All)

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemAdded, UInventoryItemComponent*, InventoryItem);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class INVENTORYANDITEMS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty, FDefaultAllocator>& OutLifetimeProps) const override;

public:

	UFUNCTION(Category = "Inventory", BlueprintCallable)
	//	This function goes through all the properties in the FromObject and transfers properties to the ToObject. NOTE: The properties need to be exactly the same name and type for the values to pass between each other
	void TransferInventoryDataToObject(UObject* FromObject, UObject* ToObject) const;

	UFUNCTION(Category = "Inventory", BlueprintCallable, BlueprintAuthorityOnly)
	bool AddItem(AActor* Item);

	UFUNCTION(Category = "Inventory", BlueprintCallable, BlueprintAuthorityOnly)
	bool RemoveItem(AActor* Item);

	UFUNCTION()
	void OnRep_Inventory();


	UPROPERTY(Category = "Inventory", BlueprintReadOnly, ReplicatedUsing=OnRep_Inventory)
	TArray<AActor*> Inventory;

	UPROPERTY(BlueprintAssignable)
	FOnItemAdded OnItemAdded;

protected:

	// Called when the game starts
	virtual void BeginPlay() override;
};