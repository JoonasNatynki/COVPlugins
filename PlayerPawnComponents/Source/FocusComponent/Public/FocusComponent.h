// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Components/ActorComponent.h"
#include <DelegateCombinations.h>
#include <CollisionQueryParams.h>
#include <GameFramework/PlayerController.h>
#include "FocusComponent.generated.h"

class APlayerCameraManager;

class FFocusComponentModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

UENUM(BlueprintType)
enum class EFocusMethod : uint8
{
	CameraDirection,
	MouseScreenPosition
};

UENUM(BlueprintType)
enum class EFocusDistanceRelativeTo : uint8
{
	PlayerPawn,
	Camera,
	PlayerPawnCapsuleBottom
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFocusedActorChanged, AActor*, NewFocusedActor);

DECLARE_LOG_CATEGORY_EXTERN(LogFocus, Log, All)

//	Component that casts either a ray from the camera or a more complex area focus mechanic to determine which object in the game world is being focused on by the player. This component can only be added to a pawn or a controller. No other types supported yet.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, meta=(ShortTooltip = "Component used for focusing on objects.") )
class FOCUSCOMPONENT_API UFocusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFocusComponent();

	UPROPERTY(BlueprintAssignable)
	FOnFocusedActorChanged OnFocusedActorChanged;

	UPROPERTY(Category = "Focus", EditDefaultsOnly, BlueprintReadWrite)
	EFocusMethod FocusMethod = EFocusMethod::CameraDirection;

	UPROPERTY(Category = "Focus", EditDefaultsOnly, BlueprintReadWrite)
	EFocusDistanceRelativeTo FocusDistanceMeasuredRelativeTo = EFocusDistanceRelativeTo::PlayerPawn;

	UPROPERTY(Category = "Focus - Transient", BlueprintReadOnly, VisibleAnywhere, Transient)
	AActor* CachedFocusedActor;

	UPROPERTY(Category = "Focus - Transient", BlueprintReadOnly, Transient)
	FVector FocusWorldLocation;

	UPROPERTY(Category = "Focus", EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "9999999.0"))
	float FocusingMaxDistance = 700.0f;

	UPROPERTY(Category = "Focus", EditDefaultsOnly, BlueprintReadWrite)
	//	How far away from the focusing center line can actors be focused at. Used in focusing on objects that are not directly being focused at
	float FocusingRadiusExtent = 50.0f;

	UPROPERTY(Category = "Focus - Debug", EditDefaultsOnly, BlueprintReadWrite)
	//	Whether to ignore all other actors but the ones with the FocusableComponent
	bool bFocusOnlyOnFocusables = true;

	UPROPERTY()
	bool bShowDebug = false;


	//	Internal implementation of the updating logic
	TWeakObjectPtr<AActor> UpdateFocusedActor_Internal();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(Category = "Focus", BlueprintCallable, BlueprintPure)
	//	Gets and updates the focused actor.
	AActor* GetFocusedActor();

	UFUNCTION(Category = "Focus", BlueprintCallable, BlueprintPure)
	//	Gets the cached focused actor from the last time the focus actor was updated.
	AActor* GetCachedFocusedActor() const;

	UFUNCTION(Category = "Focus", BlueprintCallable, BlueprintPure)
	FORCEINLINE FVector GetFocusWorldLocation() const;

	UFUNCTION(Category = "Focus", BlueprintCallable)
	//	Goes through the logic of how the focus actor is determined and updates the cached focused actor variable.
	void UpdateFocusedActor();

	UFUNCTION(Category = "Focus", BlueprintCallable)
	void SetFocusedActor(AActor* NewFocus) { CachedFocusedActor = NewFocus; };
	

private:
	const void DrawDebugs(float deltaTime);
	const TArray<FHitResult> GetOverlappingActorsInFocusArea_Internal();
	const TWeakObjectPtr<AActor> FindBestFocusCandidate_Internal(const TArray<FHitResult>& ValidHits) const;
	void UpdateFocusWorldLocation_Internal();

	FHitResult CastCrossHairLineTrace(const AActor* Character, float RayDistance) const;
	APlayerCameraManager* TryGetCameraManagerFromPawn_Internal(const APawn* Pawn) const;
	const FVector GetFocusRayCastStartLocation_Internal() const;
	const FVector GetFocusRayCastEndLocation_Internal(const FVector& StartLoc) const;
	FHitResult SimpleTraceByChannel(const UObject* InObj, const FVector& StartPos, const FVector& EndPos, ECollisionChannel Channel, const FName& TraceTag) const;
	AActor* TryGetCameraManagerActor_Internal() const;
	APlayerController* TryGetPlayerController() const;
	APawn* TryGetPlayerPawn() const;
	const FVector GetFocusDistanceRelativeLocation() const;

	float FocusInternalMaxLimit = 99999999.0f;
};

FVector UFocusComponent::GetFocusWorldLocation() const
{
	return FocusWorldLocation;
}

FORCEINLINE FHitResult UFocusComponent::SimpleTraceByChannel(const UObject* InObj, const FVector& StartPos, const FVector& EndPos, ECollisionChannel Channel, const FName& TraceTag) const
{
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(TraceTag, false);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;
	RV_TraceParams.AddIgnoredActor(Cast<AActor>(InObj));
	RV_TraceParams.TraceTag = TraceTag;

	//Re-initialize hit info
	FHitResult RV_Hit(ForceInit);

	//call GetWorld() from within an actor extending class
	bool blockingHit = InObj->GetWorld()->LineTraceSingleByChannel
	(
		RV_Hit,
		StartPos,
		EndPos,
		Channel,
		RV_TraceParams
	);
	return RV_Hit;
}