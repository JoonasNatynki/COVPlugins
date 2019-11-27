#pragma once

#include "InventoryItem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogInventoryItem, Log, All)

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class INVENTORYANDITEMS_API UInventoryItemComponent : public UActorComponent
{
	GENERATED_BODY()

	UInventoryItemComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty, FDefaultAllocator>& OutLifetimeProps) const override;

public:

	UFUNCTION()
		void OnRep_ItemGUID();

	UFUNCTION(Category = "InventoryItem", BlueprintCallable, BlueprintPure)
		FGuid& GetItemGUID() { return ItemGUID; };

	UFUNCTION(Category = "InventoryItem", BlueprintCallable, BlueprintAuthorityOnly)
		void SetItemGUID(FGuid itemGuid);

	UPROPERTY(Category = "InventoryItem", EditDefaultsOnly)
		TSubclassOf<AActor> CorrespondingActorClassToSpawn;

	UPROPERTY(Category = "InventoryItem", VisibleAnywhere, ReplicatedUsing=OnRep_ItemGUID)
		FGuid ItemGUID;

protected:

	// Called when the game starts
	virtual void BeginPlay() override;
};