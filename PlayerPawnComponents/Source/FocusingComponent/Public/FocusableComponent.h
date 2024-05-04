#pragma once

#include "CoreMinimal.h"
#include "FocusableComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFocusable, All, Log)

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCharacterFocusGained, class UFocusableComponent*, FocusableComponent, class UFocusingComponent*, FocusingComponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCharacterFocusLost, class UFocusableComponent*, FocusableComponent, class UFocusingComponent*, FocusingComponent);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFocusingCharactersChanged, class UFocusableComponent* FocusableComponent, const bool bIsFocusedBySomeone);

UENUM(BlueprintType)
enum class EFocusableDistanceMethod : uint8
{
	Distance		UMETA(ToolTip = "Simply use distance to the focusable"),
	CustomShape		UMETA(ToolTip = "Use a custom shape component on the owning actor"),
	Trigger			UMETA(ToolTip = "Use a trigger component on the owner")
};

//	A component meant for actors that are supposed to be focusable. See FocusingComponent.h
UCLASS( ClassGroup=(Focus), meta=(BlueprintSpawnableComponent), hidecategories = (Object, Rendering, Cooking, Physics, LOD, AssetUserData, Collision) )
class UFocusableComponent
	: public USceneComponent
{
	GENERATED_BODY()

friend class UFocusingComponent;

public:	
	// Sets default values for this component's properties
	UFocusableComponent(const FObjectInitializer& ObjInit);

	virtual void InitializeComponent() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Optional parameter checks the focusable state against the focusing component
	bool IsFocusable(const UFocusingComponent* FocusingComp) const;
	// Optional parameter checks the focusable state against the focusing component
	bool IsFocusableIgnoreDistance(const UFocusingComponent* FocusingComp) const;
	bool IsFocusableIgnoreDistance(const APawn* Pawn) const;
	
	//	Returns true if this focusable is currently focused by at least one focusing actor
	bool IsCurrentlyFocusedAtleastBySomeone() const;
	bool IsCurrentlyFocusedAtleastByOneLocalPlayer() const;
	float GetFocusDistance() const;

	UFUNCTION(Category="Focusable", BlueprintCallable)
	void SetFocusable(FName Context, bool bIsFocusable);
	
	// Check if the focusable is currently being manually blocked.
	bool IsFocusBlocked() const;

	//	Get all the focusing components who have a focus on this focusable
	TSet<TWeakObjectPtr<UFocusingComponent>> GetFocusingComponents() const;

	//	Method of how this focusable's determines its maximum focusable "distance"
	UPROPERTY(Category = "Focusable", EditAnywhere, BlueprintReadWrite)
	EFocusableDistanceMethod DistanceMethod = EFocusableDistanceMethod::Distance;

	//	The maximum distance this focusable can be focused at
	UPROPERTY(Category = "Focusable", EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "9999999.0", EditConditionHides, EditCondition ="DistanceMethod == EFocusableDistanceMethod::Distance"))
	float FocusableDistance = 100.0f;
	
	//	The name of the shape component on the owning actor to use as the shape that determines if this focusable is within distance to be focused at
	UPROPERTY(Category = "Focusable", EditAnywhere, meta = (EditConditionHides, EditCondition ="DistanceMethod == EFocusableDistanceMethod::CustomShape"))
	FName ShapeComponentName;
	
	// If true, will require a line-of-sight to the focusable by the camera for the focusable to be focusable
	UPROPERTY(Category = "Focusable", EditAnywhere, BlueprintReadWrite)
	bool bRequiresLineOfSight = true;

	// The angle that is required to focus on the focusable component. 180.0 being effectively a 360 degree sphere and 90.0 being a half sphere aligned to the forward vector of the focusable component
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "180.0"))
	float FocusingAimAngle = 180.0f;

	// The maximum distance this focusable can be focused on from the screen crosshair center. Lower values make it harder to focus on the focusable.
	UPROPERTY(Category = "Focusable", EditAnywhere, meta = (ClampMin = "1.0", ClampMax = "7680.0"))
	float FocusableDistanceFromCrosshairCenter = 150.0f;

	// Fires when a character has gained focus on this actor
	UPROPERTY(BlueprintAssignable)
	FOnCharacterFocusGained OnFocusGained;
	// Fires when a character has lost focus on this actor
	UPROPERTY(BlueprintAssignable)
	FOnCharacterFocusLost OnFocusLost;
	// Fired whenever focusing things have either gained or lost focus on this actor
	FOnFocusingCharactersChanged OnFocusablesChanged;

private:

	void AddFocusingPlayer(UFocusingComponent* NewFocusingComponent);
	bool RemoveFocusingPlayer(UFocusingComponent* NewFocusingComponent);

	void RemoveAllFocusingComponents();
	
	UFUNCTION()
	void OnCycleRestarted();

	TSet<FName> FocusBlockers;
	
	UPROPERTY(Transient)
	TArray<UActorComponent*> CachedConditions;

	//	Purely transient cached data of the components that are currently actively focusing on this actor
	TSet<TWeakObjectPtr<UFocusingComponent>> FocusingComponents;
};