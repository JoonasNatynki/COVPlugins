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
	Camera
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFocusedActorChanged, AActor*, NewFocusedActor);

DECLARE_LOG_CATEGORY_EXTERN(LogFocus, Log, All)

//	Component that casts either a ray from the camera or a more complex area focus mechanic to determine which object in the game world is being focused on.
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

	UPROPERTY(Category = "Focus", BlueprintReadOnly, VisibleAnywhere, Transient)
		AActor* CachedFocusedActor;

	UPROPERTY(Category = "Focus", BlueprintReadOnly, VisibleAnywhere, Transient)
		FVector FocusWorldLocation;

	UPROPERTY(Category = "Focus", EditDefaultsOnly, BlueprintReadWrite)
		float FocusingMaxDistance = 700.0f;

	UPROPERTY(Category = "Focus", EditDefaultsOnly, BlueprintReadWrite)
		//	If TRUE, you can focus on everything and on focusable things regardless of their set distance limits.
		bool bDeveloperMode = false;

	UPROPERTY(Category = "Focus", EditDefaultsOnly, BlueprintReadWrite)
		//	How far away from the focusing center line can actors be focused at. Used in focusing on objects that are not directly being focused at
		float FocusingRadiusExtent = 50.0f;

	UPROPERTY(Category = "Debug", EditDefaultsOnly, BlueprintReadWrite)
		//	Whether to ignore all other actors but the ones with the FocusableComponent
		bool bFocusOnlyOnFocusables = true;

	UPROPERTY(Category = "Debug", EditDefaultsOnly, BlueprintReadWrite)
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
		void SetFocusedActor(AActor* newFocus) { CachedFocusedActor = newFocus; };
	

private:
	const void DrawDebugs(float deltaTime);
	const TArray<FHitResult> GetOverlappingActorsInFocusArea_Internal();
	const TWeakObjectPtr<AActor> FindBestFocusCandidate_Internal(TArray<FHitResult> overlappingActors);
	void UpdateFocusWorldLocation_Internal();

	FHitResult CastCrossHairLineTrace(const AActor* character, float rayDistance);
	APlayerCameraManager* TryGetCameraManager(const APawn* pawn) const;
	FVector GetFocusRayCastStartLocation_Internal();
	FVector GetFocusRayCastEndLocation_Internal(const FVector& startLoc);
	FHitResult SimpleTraceByChannel(const UObject* inObj, const FVector& startPos, const FVector& endPos, ECollisionChannel channel, const FName& TraceTag) const;
	AActor* TryGetCameraManagerActor_Internal() const;
	APlayerController* TryGetPlayerController() const;
	APawn* TryGetPlayerPawn() const;
	const FVector GetFocusDistanceRelativeLocation() const;
};

FVector UFocusComponent::GetFocusWorldLocation() const
{
	return FocusWorldLocation;
}

FORCEINLINE FHitResult UFocusComponent::SimpleTraceByChannel(const UObject* inObj, const FVector& startPos, const FVector& endPos, ECollisionChannel channel, const FName& TraceTag) const
{
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(TraceTag, false);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;
	RV_TraceParams.AddIgnoredActor(Cast<AActor>(inObj));
	RV_TraceParams.TraceTag = TraceTag;

	//Re-initialize hit info
	FHitResult RV_Hit(ForceInit);

	//call GetWorld() from within an actor extending class
	bool blockingHit = inObj->GetWorld()->LineTraceSingleByChannel
	(
		RV_Hit,
		startPos,
		endPos,
		channel,
		RV_TraceParams
	);
	return RV_Hit;
}

FORCEINLINE FHitResult UFocusComponent::CastCrossHairLineTrace(const AActor* Character, float RayDistance)
{
	FHitResult RV_Hit(ForceInit);

	const APlayerController* PlayerController = TryGetPlayerController();
	const AActor* CameraManagerActor = TryGetCameraManagerActor_Internal();

	if (ensure(IsValid(CameraManagerActor)))
	{

		//	Ray starting point
		const FVector PlayerViewWorldLocation = CameraManagerActor->GetActorLocation();
		FVector ControllerForwardVector;

		switch (FocusMethod)
		{
		case(EFocusMethod::CameraDirection):
			{
				//	end point target direction
				ControllerForwardVector = CameraManagerActor->GetActorForwardVector();
				break;
			}
		case(EFocusMethod::MouseScreenPosition):
			{
				FVector WorldLocation;
				FVector WorldDirection;
				PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
				ControllerForwardVector = PlayerViewWorldLocation + (PlayerViewWorldLocation + (WorldDirection));
			}
		}

		RV_Hit = SimpleTraceByChannel
		(
			Character,
			PlayerViewWorldLocation + (ControllerForwardVector),
			PlayerViewWorldLocation + (ControllerForwardVector * RayDistance),
			ECollisionChannel::ECC_Camera,
			FName("AimTrace")
		);

		return RV_Hit;
	}

	return RV_Hit;
}