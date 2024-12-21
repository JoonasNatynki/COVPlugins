#include "FocusingComponent.h"
#include "Components/CapsuleComponent.h"
#include "FocusableComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/UObjectIterator.h"
#include "ConvexVolume.h"
#include "UE4Helpers.h"

void FFocusingComponentModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}
void FFocusingComponentModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

namespace MagicNumbers
{
	static constexpr float TICKRATE_OF_FOCUSING_COMPONENT_DEBUGSTUFF = 0.0333f;
}

DEFINE_LOG_CATEGORY(LogFocusingComponent)

// Sets default values for this component's properties
UFocusingComponent::UFocusingComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = ETickingGroup::TG_PostUpdateWork;
	PrimaryComponentTick.TickInterval = MagicNumbers::TICKRATE_OF_FOCUSING_COMPONENT_DEBUGSTUFF;
	bAutoActivate = true;
}

void UFocusingComponent::Activate(bool bReset)
{
	Super::Activate(bReset);
}

void UFocusingComponent::Deactivate()
{
	Super::Deactivate();

	if (CachedFocusedActor.IsValid())
	{
		SetFocusedActor(nullptr);
	}
}

const APlayerCameraManager* UFocusingComponent::GetCameraManager() const
{
	if (const APlayerController* PlayerController = GetPlayerController())
	{
		return PlayerController->PlayerCameraManager;
	}

	return nullptr;
}

FVector UFocusingComponent::GetFocusRayCastStartLocation_Internal() const
{
	const AActor* OwnerCameraManagerActor = GetCameraManager();
	FVector StartLoc;

	//	If owner doesn't have a camera manager present, just use pawn forward vector instead(?)
	(OwnerCameraManagerActor) ?
		StartLoc = OwnerCameraManagerActor->GetActorLocation() :
		StartLoc = GetOwner()->GetActorLocation();
	
	return StartLoc;
}

const APlayerController* UFocusingComponent::GetPlayerController() const
{
	const APawn* AsPawn = GetPlayerPawn();
	if(IsValid(AsPawn))
	{
		const APlayerController* AsPlayerController = Cast<APlayerController>(AsPawn->GetController());
		if(IsValid(AsPlayerController))
		{
			return AsPlayerController;
		}
	}

	return nullptr;
}

const APawn* UFocusingComponent::GetPlayerPawn() const
{
	const APawn* OwnerPawn = Cast<APawn>(GetOwner());	
	check(IsValid(OwnerPawn));
	return OwnerPawn;
}

FVector UFocusingComponent::GetLocationFromWhereFocusDistanceIsCalculated() const
{
	switch (FocusDistanceMeasuredRelativeTo)
	{
		case(EFocusDistanceRelativeTo::PlayerPawn):
		{
			return GetPlayerPawn()->GetActorLocation();
		}
		case(EFocusDistanceRelativeTo::Camera):
		{
			const APlayerCameraManager* PCM = GetCameraManager();
			if(!IsValid(PCM))
			{
				return FVector::ZeroVector;
			}

			return Cast<AActor>(PCM)->GetActorLocation();
		}
		case(EFocusDistanceRelativeTo::PlayerPawnCapsuleBottom):
		{
			const APawn* Pawn = GetPlayerPawn();
			return Pawn->GetActorLocation() - FVector(0,0,Cast<ACharacter>(Pawn)->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
		}
	}

	return FVector::ZeroVector;
}

AActor* UFocusingComponent::TryGetBestFocusedActorCandidate_Internal()
{
	AActor* FocusedActor = nullptr;
	UpdateWorldFocusHitResult_Internal();

	//	Compile the candidates into one array
	TArray<AActor*, TInlineAllocator<100>> AllCandidateActors;
	for (TObjectIterator<UFocusableComponent> ComponentIt; ComponentIt; ++ComponentIt)
	{
		if(ComponentIt &&
			IsValid(*ComponentIt) &&
			!ComponentIt->IsTemplate() &&
			GetWorld() == ComponentIt->GetWorld() &&
			ComponentIt->IsFocusable(this))
		{
			// Early prune out focusables that don't meet distance/area requirements
			if (!DoesFocusableMeetAreaRequirements(*ComponentIt))
			{
				continue;
			}
			
			AllCandidateActors.Add(ComponentIt->GetOwner());
		}
	}
	
	//	Now go through all the overlapping actors and figure out the best candidate that the player might actually intend on focusing
	if (AllCandidateActors.Num() > 0)
	{
		AActor* BestCandidate = FindBestFocusCandidateFromActors(AllCandidateActors);
		FocusedActor = BestCandidate;
	}

	return FocusedActor;
}

const TWeakObjectPtr<AActor> UFocusingComponent::UpdateCachedFocusedActor()
{
	UpdateFocus();
	return CachedFocusedActor;
}

const TWeakObjectPtr<AActor> UFocusingComponent::GetCachedFocusedActor() const
{
	return CachedFocusedActor;
}

FVector UFocusingComponent::GetFocusWorldLocation() const
{
	return WorldFocusHitResult.ImpactPoint;
}

FHitResult UFocusingComponent::GetWorldFocusHitResult() const
{
	return WorldFocusHitResult;
}

void UFocusingComponent::UpdateFocus()
{
	// If cached actor was not found, try to find a new actor to focus at
	AActor* NewFocusActor = TryGetBestFocusedActorCandidate_Internal();

	if (CachedFocusedActor != NewFocusActor)
	{
		SetFocusedActor(NewFocusActor);
	}
}

void UFocusingComponent::SetFocusedActor(AActor* NewFocusActor)
{
	//	Focused actor has changed
	TWeakObjectPtr<AActor> OldFocusActor = CachedFocusedActor;
	CachedFocusedActor = NewFocusActor;
	
	if (OldFocusActor.IsValid())
	{
		//	Remove cached focus information from the focusable
		if (UFocusableComponent* FocusableComponent = OldFocusActor->FindComponentByClass<UFocusableComponent>())
		{
			FocusableComponent->RemoveFocusingPlayer(this);
		}
	}

	if (IsValid(NewFocusActor))
	{
		//	Make the focused actor know it is being focused at currently
		UFocusableComponent* FocusableComponent = NewFocusActor->FindComponentByClass<UFocusableComponent>();
		check(IsValid(FocusableComponent));
		FocusableComponent->AddFocusingPlayer(this);
	}
	
	UE_LOG(LogFocusingComponent, Log, TEXT("Focus actor changed to (%s)."), *GetNameSafe(CachedFocusedActor.Get()));
	OnFocusedActorChanged.Broadcast(NewFocusActor);
}

TArray<FHitResult> UFocusingComponent::GetOverlappingActorsInFocusArea_Internal() const
{
	TArray<FHitResult> Hits;
	TArray<FHitResult> ValidHits;
	const APlayerController* PlayerController = GetPlayerController();

	if(!IsValid(PlayerController))
	{
		return ValidHits;
	}
	
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());

	const FVector StartLoc = GetFocusRayCastStartLocation_Internal();
	const FVector& EndLoc = StartLoc + FVector(0.0f,0.0f,1.0f);

	FConvexVolume ViewFrustrum;
	const bool bHasViewFrustrum = UE4CodeHelpers::GetPlayerViewFrustum(PlayerController, ViewFrustrum);
	
	UKismetSystemLibrary::SphereTraceMulti(this,
		StartLoc,
		EndLoc,
		FocusingMaxDistance,
		UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2),
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		Hits,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		GetWorld()->GetDeltaSeconds());

	if (Hits.Num() > 0)
	{
		for (auto& Hit : Hits)
		{
			const AActor* HitActor = Hit.GetActor();

			if(!IsValid(HitActor))
			{
				continue;
			}

			//	Strip out actors that are not in "view"
			if(bHasViewFrustrum)
			{
				FVector BoundsCenter;
				FVector BoundsExtend;
				HitActor->GetActorBounds(false, BoundsCenter, BoundsExtend);
				const bool bIsInView = ViewFrustrum.IntersectBox(BoundsCenter, BoundsExtend);
				if(!bIsInView)
				{
					continue;
				}
			}
			
			UFocusableComponent* FocusableComp = HitActor->FindComponentByClass<UFocusableComponent>();
			if (IsValid(FocusableComp) && FocusableComp->IsFocusable(this))
			{
				ValidHits.Add(Hit);
			}
		}
	}

	return ValidHits;
}

FHitResult SimpleTraceByChannel(const UObject* InObj, const FVector& StartPos, const FVector& EndPos, ECollisionChannel Channel, const FName& TraceTag)
{
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(TraceTag, false);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.AddIgnoredActor(Cast<AActor>(InObj));
	RV_TraceParams.TraceTag = TraceTag;

	//Re-initialize hit info
	FHitResult RV_Hit(ForceInit);

	InObj->GetWorld()->LineTraceSingleByChannel
    (
        RV_Hit,
        StartPos,
        EndPos,
        Channel,
        RV_TraceParams
    );
	return RV_Hit;
}

AActor* UFocusingComponent::FindBestFocusCandidateFromActors(const TArray<AActor*, TInlineAllocator<100>>& CandidateActors) const
{
	AActor* Candidate = nullptr;
	float BestScore = FLT_MIN;
	const APlayerController* PC = GetPlayerController();

	if(!IsValid(PC))
	{
		return nullptr;
	}

	//	Here we get the viewport coordinates to the crosshair center
	int32 ViewportSizeX = 0;
	int32 ViewportSizeY = 0;
	PC->GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2d ViewportCrosshairCenter(ViewportSizeX/2, ViewportSizeY/2);
	const float ViewportXYSize = FVector2d(ViewportSizeX, ViewportSizeY).Length();
	
	for (auto&& CandidateActor : CandidateActors)
	{
		//	Gather up all the data!!
		FVector ScreenSpaceHitLocation;
		UFocusableComponent* FocusableComponent = CandidateActor->FindComponentByClass<UFocusableComponent>();
		const FVector& CandidateFocusableComponentLocation = FocusableComponent->GetComponentLocation();
		PC->ProjectWorldLocationToScreenWithDistance(CandidateFocusableComponentLocation, ScreenSpaceHitLocation);		
		const FVector2d& ScreenSpaceLocation = FVector2d(ScreenSpaceHitLocation);
		
		const FVector FocusSourceLocation = GetLocationFromWhereFocusDistanceIsCalculated();
		const float& DistanceToFocusableComponentFromActorWhoIsFocusing = (FocusSourceLocation - CandidateFocusableComponentLocation).Size();	//	Used for trimming results
		const float& HitActorDistanceFromCrosshairCenter = (ScreenSpaceLocation - ViewportCrosshairCenter).Length();
		float HitActorFocusScore = ViewportXYSize/2 - (ScreenSpaceLocation - ViewportCrosshairCenter).Length();

		FVector FocusingActorUnitVectorLocation = (GetOwner()->GetActorLocation() - FocusableComponent->GetComponentLocation());
		FocusingActorUnitVectorLocation.Normalize();
		const float AimAtAngle = (FMath::Acos(FVector::DotProduct(FocusableComponent->GetForwardVector(), FocusingActorUnitVectorLocation))) * (180.0f / UE_PI);
		
		check(IsValid(FocusableComponent));
		
		

		//	Modify the radius with the viewport size
		const float ModifiedScreenSpaceRadius = GetModifiedScreenSpaceCrosshairDistance(FocusableComponent);
		
		// Do the LOS check to the candidate
		FCollisionQueryParams RV_TraceParams = FCollisionQueryParams("LOSCheck", false);
		RV_TraceParams.bTraceComplex = true;
		RV_TraceParams.AddIgnoredActor(GetOwner());
		RV_TraceParams.AddIgnoredActor(CandidateActor);

		FHitResult LOS_Hit(ForceInit);
		// No point doing LOS checks for things that don't need it
		if (FocusableComponent->bRequiresLineOfSight)
		{
			GetOwner()->GetWorld()->LineTraceSingleByChannel
			(
				LOS_Hit,
				GetFocusRayCastStartLocation_Internal(),
				FocusableComponent->GetComponentLocation(),
				ECollisionChannel::ECC_Visibility,
				RV_TraceParams
			);
		}
		
		//	Now use the data!
		/*
		const FColor ColorOfFocusSourceReachDistance = ((DistanceToFocusableComponentFromActorWhoIsFocusing < FocusableComponent->GetFocusDistance() &&
				FocusableComponent->DistanceMethod == EFocusableDistanceMethod::Distance)
				&& !LOS_Hit.bBlockingHit)?
				(FColor::Green):(FColor::Red);

        DrawDebugPoint(
            GetWorld(),
            CandidateFocusableComponentLocation,
            10.0f,
            ColorOfFocusSourceReachDistance,
            false,
            MagicNumbers::TICKRATE_OF_FOCUSING_COMPONENT_DEBUGSTUFF
		);
            
        const FString FullDebugString = (LOS_Hit.bBlockingHit)?(FString("NO LINE OF SIGHT")):
        (
            FString("Score: ") +
            FString::SanitizeFloat((int32)HitActorFocusScore) +
            FString("\n") +
            FString("Max dist from X-hair: ") + FString::SanitizeFloat((int32)HitActorDistanceFromCrosshairCenter) +
            FString(" / ") +
            FString::SanitizeFloat((int32)ModifiedScreenSpaceRadius) +
            FString("\n") +
            FString("Angle to focus forward: ") + FString::SanitizeFloat(AimAtAngle)
        );
			
        DrawDebugString(
            GetWorld(),
            CandidateFocusableComponentLocation + FVector(0,0,-40.0f),
            FullDebugString,
            nullptr,
            ColorOfFocusSourceReachDistance,
            MagicNumbers::TICKRATE_OF_FOCUSING_COMPONENT_DEBUGSTUFF,
            true
            );

        const FColor CrosshairDistanceCircleColor = (HitActorDistanceFromCrosshairCenter < ModifiedScreenSpaceRadius)?(FColor::Green):(FColor::Red);
        
        HMQDrawDebug2D::DrawCircle(
            ScreenSpaceLocation.X,
            ScreenSpaceLocation.Y,
            ModifiedScreenSpaceRadius,
            32,
            CrosshairDistanceCircleColor,
            MagicNumbers::TICKRATE_OF_FOCUSING_COMPONENT_DEBUGSTUFF,
            1.8f
            );
        */

		if(!IsFocusableRelevantForCandidateConsideration_Internal(FocusableComponent, DistanceToFocusableComponentFromActorWhoIsFocusing, HitActorDistanceFromCrosshairCenter, AimAtAngle, LOS_Hit))
		{
			continue;
		}

		//	Is this actor a better candidate?
		if (HitActorFocusScore > BestScore)
		{
			Candidate = CandidateActor;
			BestScore = HitActorFocusScore;
		}
	}

	return Candidate;
}

bool UFocusingComponent::IsFocusableRelevantForCandidateConsideration_Internal(
	const UFocusableComponent* FocusableComponent,
	const float DistanceToActorWhoIsFocusing,
	const float HitActorDistanceFromCrosshairCenter,
	const float AimAtAngle,
	const FHitResult& LOS_Hit) const
{
	if (AimAtAngle > FocusableComponent->FocusingAimAngle)
	{
		return false;
	}
	
	if (FocusableComponent->bRequiresLineOfSight && LOS_Hit.bBlockingHit)
	{
		return false;
	}

	// If the focusable is basically at the focusing actor's "feet" or right up touching it, we can consider it a valid candidate past this point
	if (DistanceToActorWhoIsFocusing > FeetFocusingDistance)
	{
		const float FocusableDistanceFromCrosshairCenter = GetModifiedScreenSpaceCrosshairDistance(FocusableComponent);
		if (HitActorDistanceFromCrosshairCenter > FocusableDistanceFromCrosshairCenter)
		{
			return false;
		}
	}

	//	All checks pass, good to go
	return true;
}

void UFocusingComponent::UpdateWorldFocusHitResult_Internal()
{
	const FHitResult RV_Hit = CastCrossHairLineTrace(GetOwner(), FocusingMaxDistance);
	WorldFocusHitResult = RV_Hit;
}

FHitResult UFocusingComponent::CastCrossHairLineTrace(const AActor* Character, float RayDistance) const
{
	const APlayerController* PlayerController = GetPlayerController();
	const AActor* CameraManagerActor = GetCameraManager();
	FHitResult RV_Hit(ForceInit);

	if(!IsValid(PlayerController))
	{
		return RV_Hit;
	}
	
	if (IsValid(CameraManagerActor))
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
				ControllerForwardVector = WorldDirection;
				break;
			}
		}

		// Do the x-hair aim trace
		FCollisionQueryParams RV_TraceParams = FCollisionQueryParams("AimTrace", false);
		RV_TraceParams.bTraceComplex = true;
		RV_TraceParams.AddIgnoredActor(Character);

		Character->GetWorld()->LineTraceSingleByChannel
        (
            RV_Hit,
            PlayerViewWorldLocation,
            PlayerViewWorldLocation + (ControllerForwardVector * RayDistance),
            ECollisionChannel::ECC_Visibility,
            RV_TraceParams
        );

		return RV_Hit;
	}

	return RV_Hit;
}

float UFocusingComponent::GetModifiedScreenSpaceCrosshairDistance(const UFocusableComponent* FocusableComponent) const
{
	if(const APlayerController* PC = GetPlayerController())
	{
		int32 ViewportSizeX = 0;
		int32 ViewportSizeY = 0;
		PC->GetViewportSize(ViewportSizeX, ViewportSizeY);
		float ViewportSizeMultiplier = (float)ViewportSizeX / (1920.0f);	//	We use 1920 as the default 1:1 scale
		return FocusableComponent->FocusableDistanceFromCrosshairCenter * ViewportSizeMultiplier;
	}

	return 0.0f;
}

const void UFocusingComponent::DrawDebugs(const float deltaTime) const
{
	/*
	HMQ_DRAW_DEBUG_CODE
	(
		const FVector FocusingSourceLocation = GetLocationFromWhereFocusDistanceIsCalculated();
        UWorld* World = GetWorld();		
        const FVector WorldFocusLocation = GetFocusWorldLocation();
            
		if(HMQ_DRAW_DEBUG_IS_ACTIVE())
		{
			//	Focus location crosshair
			if(!WorldFocusLocation.IsZero())
			{
			 DrawDebugCrosshairs(
				 World,
				 WorldFocusLocation,
				 FRotator::ZeroRotator,
				 50.0f,
				 FColor::Red,
				 false,
				 deltaTime,
				 0
			 );
			}

			DrawDebugCrosshairs(
				 World,
				 FocusingSourceLocation,
				 FRotator::ZeroRotator,
				 50.0f,
				 FColor::Red,
				 false,
				 deltaTime,
				 0
			 );

			DrawDebugSphere(
				 World,
				 FocusingSourceLocation,
				 FocusingMaxDistance,
				 16,
				 FColor::Cyan,
				 false,
				 deltaTime,
				 0,
				 1.0f
			 );

			//	Focused actor name on focused actor
			DrawDebugString(
				 World,
				 (CachedFocusedActor.IsValid())?(CachedFocusedActor->GetActorLocation()):(WorldFocusLocation),
				 FString("Focused actor: ") + GetNameSafe(CachedFocusedActor.Get()),
				 nullptr,
				 FColor::Magenta,
				 deltaTime,
				 true,
				 1
			 );
		}

		const bool bIsDebugActive = HMQ_DRAW_DEBUG_IS_ACTIVE();
		
		//	Draw every focusable actor possible focus reach radius
		for(FActorIterator ActorIter(World); ActorIter; ++ActorIter)
		{
			const AActor* Actor = *ActorIter;
			if(const UFocusableComponent* FocusComp = Actor->FindComponentByClass<UFocusableComponent>())
			{
				if(FocusComp->DistanceMethod == EFocusableDistanceMethod::Distance)
				{
					const FColor ColorOfFocusableReachRadius =
						((FocusingSourceLocation - Actor->GetActorLocation()).Size()<= FocusComp->GetFocusDistance() || Actor == GetCachedFocusedActor())
						? (FColor::Green)
						: (FColor::Red);
					DrawDebugLine(World, Actor->GetActorLocation(), Actor->GetActorLocation() + FVector(0,0, FocusComp->GetFocusDistance()), ColorOfFocusableReachRadius, false, -1.0f, 0, 2.0f);
					DrawDebugSphere(World, Actor->GetActorLocation(), FocusComp->GetFocusDistance(), 6, ColorOfFocusableReachRadius, false, -1.0f, 0, 1.0f);
				}
				else if(FocusComp->DistanceMethod == EFocusableDistanceMethod::CustomShape)
				{
					UActorComponent* ComponentReference = UHMQGameBlueprintLibrary::GetActorComponentByName(FocusComp->GetOwner(), FocusComp->ShapeComponentName);
					if(IsValid(ComponentReference))
					{
						Cast<UShapeComponent>(ComponentReference)->SetHiddenInGame(!bIsDebugActive);
					}
				}
			}
		}
	)
	*/
}

void UFocusingComponent::HandleStartDeath(const FStartDeathData& Data)
{
	Deactivate();
}

bool UFocusingComponent::IsFocusableCloseEnoughToBeFocusedAt(const UFocusableComponent* Focusable) const
{
	const FVector FocusingComponentFocusingOriginPoint = GetLocationFromWhereFocusDistanceIsCalculated();
	const float DistanceToFocusingComponentThatIsFocusing = (FocusingComponentFocusingOriginPoint - Focusable->GetComponentLocation()).Size();
	return DistanceToFocusingComponentThatIsFocusing <= Focusable->GetFocusDistance();
}

bool UFocusingComponent::IsFocusableInCustomShapeVolume(const UFocusableComponent* Focusable) const
{
	if(ensure(!Focusable->ShapeComponentName.IsNone()))
	{
		UActorComponent* ComponentReference = UE4CodeHelpers::GetComponentByName(Focusable->GetOwner(), Focusable->ShapeComponentName);
		if (ensureMsgf(IsValid(ComponentReference), TEXT("Focusable component on (%s) did not have a valid component reference for the custom shape by name (%s).Without a valid custom shape the focusable can't determine if it is range of being able to be focused at"),
				*GetNameSafe(Focusable->GetOwner()),
				*Focusable->ShapeComponentName.ToString()))
		{
			UShapeComponent* AsShape = Cast<UShapeComponent>(ComponentReference);
			if(ensureMsgf(IsValid(AsShape), TEXT("Component (%s) being referred to on (%s) by its focusable component is not a shape type. Can not determine the shape of it."),
				*Focusable->ShapeComponentName.ToString(),
				*GetNameSafe(Focusable->GetOwner())))
			{
				return AsShape->IsOverlappingActor(GetOwner());
			}
		}
	}

	return false;
}

bool UFocusingComponent::DoesFocusableMeetAreaRequirements(const UFocusableComponent* Focusable) const
{
	switch(Focusable->DistanceMethod)
	{
		case EFocusableDistanceMethod::Distance:
			{
				return IsFocusableCloseEnoughToBeFocusedAt(Focusable);	
			}
		case EFocusableDistanceMethod::CustomShape:
			{
				return IsFocusableInCustomShapeVolume(Focusable);
			}
		case EFocusableDistanceMethod::Trigger:
			{
				return Focusable->IsActive();
			}
		default: break;
	}

	return false;
}

// Called every frame
void UFocusingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	QUICK_SCOPE_CYCLE_COUNTER(UFocusingComponent_Tick);

	APawn* AsPawn = Cast<APawn>(GetOwner());
	if (IsValid(AsPawn))
	{
		// If not controlled locally, don't update focus
		if (!AsPawn->IsLocallyControlled())
		{
			SetFocusedActor(nullptr);
			return;
		}
		
		UpdateFocus();
		DrawDebugs(DeltaTime);
	}
}

#undef HMQ_DRAW_DEBUG_NAME

IMPLEMENT_MODULE(FFocusingComponentModule, FocusingComponent)