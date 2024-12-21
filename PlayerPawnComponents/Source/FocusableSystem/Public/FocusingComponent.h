#pragma once

#include "CoreMinimal.h"
#include "Engine/HitResult.h"
#include "FocusingComponent.generated.h"

struct FStartDeathData;
class APlayerCameraManager;
class UFocusableComponent;

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

DECLARE_MULTICAST_DELEGATE_OneParam(FOnFocusedActorChanged, AActor* NewFocusedActor);

DECLARE_LOG_CATEGORY_EXTERN(LogFocusingComponent, Log, All);

//	This component handles the responsibility of focusing on world actors for the player for the player to interact, inspect and use
UCLASS( ClassGroup=(Focus), meta=(BlueprintSpawnableComponent), hidecategories = (Object, Rendering, Cooking, Physics, LOD, AssetUserData, Collision) )
class UFocusingComponent : public UActorComponent
{
	GENERATED_BODY()

	friend class UFocusableComponent;

public:	
	UFocusingComponent(const FObjectInitializer& ObjectInitializer);

	//	Updates and returns the current up-to-date focused actor
	const TWeakObjectPtr<AActor> UpdateCachedFocusedActor();
	//	Gets the current cached focused actor. Does not run the actual update logic.
	const TWeakObjectPtr<AActor> GetCachedFocusedActor() const;
	FVector GetFocusWorldLocation() const;
	FHitResult GetWorldFocusHitResult() const;
	//	Bind into this if you want to listen to the focused actor changes
	FOnFocusedActorChanged OnFocusedActorChanged;

	virtual void Activate(bool bReset) override;
	virtual void Deactivate() override;

	const APlayerController* GetPlayerController() const;
	const APawn* GetPlayerPawn() const;
	
private:
	const APlayerCameraManager* GetCameraManager() const;
	FVector GetFocusRayCastStartLocation_Internal() const;
	FVector GetLocationFromWhereFocusDistanceIsCalculated() const;
	AActor* TryGetBestFocusedActorCandidate_Internal();
	void UpdateFocus();
	void SetFocusedActor(AActor* NewFocusActor);
	const void DrawDebugs(const float deltaTime) const;
	TArray<FHitResult> GetOverlappingActorsInFocusArea_Internal() const;
	AActor* FindBestFocusCandidateFromActors(const TArray<AActor*, TInlineAllocator<100>>& CandidateActors) const;
	bool IsFocusableRelevantForCandidateConsideration_Internal(
		const class UFocusableComponent* FocusableComponent,
		const float DistanceToActorWhoIsFocusing,
		const float HitActorDistanceFromCrosshairCenter,
		const float AimAtAngle,
		const FHitResult& LOS_Hit
		) const;
	void UpdateWorldFocusHitResult_Internal();
	FHitResult CastCrossHairLineTrace(const AActor* Character, float RayDistance) const;
	//	Gets the radius of the focusing distance from the screen center crosshair, modified with the viewport X axis resolution.
	float GetModifiedScreenSpaceCrosshairDistance(const UFocusableComponent* FocusableComponent) const;
	void HandleStartDeath(const FStartDeathData& Data);
	bool IsFocusableCloseEnoughToBeFocusedAt(const UFocusableComponent* Focusable) const;
	bool IsFocusableInCustomShapeVolume(const UFocusableComponent* Focusable) const;
	bool DoesFocusableMeetAreaRequirements(const UFocusableComponent* Focusable) const;

	UPROPERTY(EditDefaultsOnly)
	EFocusMethod FocusMethod = EFocusMethod::CameraDirection;

	UPROPERTY(EditDefaultsOnly)
	EFocusDistanceRelativeTo FocusDistanceMeasuredRelativeTo = EFocusDistanceRelativeTo::PlayerPawn;

	TWeakObjectPtr<AActor> CachedFocusedActor;
	FHitResult WorldFocusHitResult;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0.0", ClampMax = "9999999.0"))
	float FocusingMaxDistance = 2000.0f;

	// If a focusable is withing this distance to the Focusing source location defined by FocusDistanceMeasuredRelativeTo, then the focusable is always considered a valid candidate for focusing if it is still on screen
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0.0", ClampMax = "9999999.0"))
	float FeetFocusingDistance = 100.0f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	
};

class FFocusingComponentModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};