// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FocusComponent.h"
#include <DrawDebugHelpers.h>
#include <Kismet/KismetSystemLibrary.h>
#include "FocusableComponent.h"
#include <Engine/EngineTypes.h>
#include <MessageLog.h>
#include <GameFramework/Controller.h>
#include <GameFramework/Pawn.h>
#include <UObjectToken.h>

#define LOCTEXT_NAMESPACE "FFocusComponentModule"

void FFocusComponentModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FFocusComponentModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

static TAutoConsoleVariable<int32> CVarShowFocusDebugs(TEXT("COV.DebugFocusPoint"),
	0,
	TEXT("Show the point of focus in the world."));

DEFINE_LOG_CATEGORY(LogFocus)

// Sets default values for this component's properties
UFocusComponent::UFocusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = ETickingGroup::TG_PostUpdateWork;
}

// Called when the game starts
void UFocusComponent::BeginPlay()
{
	Super::BeginPlay();
}

APlayerCameraManager* UFocusComponent::TryGetCameraManagerFromPawn_Internal(const APawn* Pawn) const
{
	if (!IsValid(Pawn))
	{
		FMessageLog("PIE").Error(FText::FromString("Could not get pawn camera manager. Pawn wasn't valid."));
		return nullptr;
	}
	
	APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());

	if (!IsValid(PlayerController))
	{
		//FMessageLog("PIE").Error(FText::FromString("Could not get pawn camera manager. The pawn's controller was not valid."))->AddToken(FUObjectToken::Create(pawn));
		return nullptr;
	}

	if (!ensureMsgf(IsValid(PlayerController->PlayerCameraManager), TEXT("The player camera manager was not valid.")))
	{
		FMessageLog("PIE").Error(FText::FromString("Could not get pawn camera manager. The camera manager was not valid for pawn."))->AddToken(FUObjectToken::Create(Pawn));
		return nullptr;
	}

	return PlayerController->PlayerCameraManager;
}

const FVector UFocusComponent::GetFocusRayCastStartLocation_Internal() const
{
	const AActor* OwnerCameraManagerActor = TryGetCameraManagerActor_Internal();
	FVector StartLoc;

	//	If owner doesn't have a camera manager present, just use pawn forward vector instead(?)
	if (OwnerCameraManagerActor)
	{
		StartLoc = OwnerCameraManagerActor->GetActorLocation();
	}
	else
	{
		StartLoc = GetOwner()->GetActorLocation();
	}

	return StartLoc;
}

const FVector UFocusComponent::GetFocusRayCastEndLocation_Internal(const FVector& StartLoc) const
{
	const AActor* OwnerCameraManagerActor = TryGetCameraManagerActor_Internal();
	FVector EndLoc;

	//	If owner doesn't have a camera manager present, just use pawn forward vector instead(?)
	if (OwnerCameraManagerActor)
	{
		switch (FocusMethod)
		{
		case(EFocusMethod::CameraDirection):
			{
				//	end point target direction
				const FVector& StartLocation = OwnerCameraManagerActor->GetActorLocation();
				EndLoc = StartLocation + (OwnerCameraManagerActor->GetActorForwardVector() * FocusingMaxDistance);
				break;
			}
		case(EFocusMethod::MouseScreenPosition):
			{
				const APlayerController* PlayerController = TryGetPlayerController();
				FVector WorldLocation;
				FVector WorldDirection;
				PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
				EndLoc = WorldLocation + (WorldDirection * FocusingMaxDistance);
				break;
			}
		}
	}
	else
	{
		EndLoc = StartLoc + (GetOwner()->GetActorForwardVector() * FocusingMaxDistance);
	}

	return EndLoc;
}

AActor* UFocusComponent::TryGetCameraManagerActor_Internal() const
{
	const APawn* Pawn = TryGetPlayerPawn();
	if (IsValid(Pawn))
	{
		return Cast<AActor>(TryGetCameraManagerFromPawn_Internal(Pawn));
	}

	return nullptr;
}

APlayerController* UFocusComponent::TryGetPlayerController() const
{
	APlayerController* PlayerController = nullptr;

	const APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (IsValid(OwnerPawn))
	{
		PlayerController = Cast<APlayerController>(OwnerPawn->GetController());
	}
	else
	{
		AController* OwnerController = Cast<AController>(GetOwner());
		if (IsValid(OwnerController))
		{
			PlayerController = Cast<APlayerController>(OwnerController);
		}
	}

	check(IsValid(PlayerController));
	return PlayerController;
}

APawn* UFocusComponent::TryGetPlayerPawn() const
{
	//	If this component is on a pawn
	APawn* OwnerPawn = Cast<APawn>(GetOwner());	
	if (IsValid(OwnerPawn))
	{
		return OwnerPawn;
	}

	//	If this component is on a controller
	AController* OwnerController = Cast<AController>(GetOwner());
	if (IsValid(OwnerController))
	{
		OwnerPawn = OwnerController->GetPawn();
		if (IsValid(OwnerPawn))
		{
			return OwnerPawn;
		}
	}

	return nullptr;
}

const FVector UFocusComponent::GetFocusDistanceRelativeLocation() const
{
	switch (FocusDistanceMeasuredRelativeTo)
	{
		case(EFocusDistanceRelativeTo::PlayerPawn):
		{
			return TryGetPlayerPawn()->GetActorLocation();
		}
		case(EFocusDistanceRelativeTo::Camera):
		{
			return TryGetCameraManagerActor_Internal()->GetActorLocation();
		}
	}

	return FVector::ZeroVector;
}

TWeakObjectPtr<AActor> UFocusComponent::UpdateFocusedActor_Internal()
{
	TWeakObjectPtr<AActor> FocusedActor;
	UpdateFocusWorldLocation_Internal();
	const TArray<FHitResult>& ValidHits = GetOverlappingActorsInFocusArea_Internal();

	//	Now go through all the overlapping actors and figure out the best candidate that the player might actually intend on focusing
	if (ValidHits.Num() > 0)
	{
		const TWeakObjectPtr<AActor>& BestCandidate = FindBestFocusCandidate_Internal(ValidHits);
		FocusedActor = BestCandidate;
	}

	return FocusedActor;
}

AActor* UFocusComponent::GetFocusedActor()
{
	UpdateFocusedActor();
	return CachedFocusedActor;
}

AActor* UFocusComponent::GetCachedFocusedActor() const
{
	return CachedFocusedActor;
}

void UFocusComponent::UpdateFocusedActor()
{
	//	If cached actor was not found, try to find a new actor to focus at
	const TWeakObjectPtr<AActor>& NewFocusActor = UpdateFocusedActor_Internal();
	
	const bool bFocusActorHasChanged = (CachedFocusedActor != NewFocusActor) ? (true) : (false);

	if (bFocusActorHasChanged)
	{
		CachedFocusedActor = NewFocusActor.Get();
		UE_LOG(LogFocus, Verbose, TEXT("Focus actor changed to (%s)."), *GetNameSafe(CachedFocusedActor));
		OnFocusedActorChanged.Broadcast(NewFocusActor.Get());
	}
}

const void UFocusComponent::DrawDebugs(float deltaTime)
{
	DrawDebugSphere(GetWorld(), CastCrossHairLineTrace(GetOwner(), FocusingMaxDistance).ImpactPoint, 5.0f, 4, FColor::Magenta, false, -1.0f, 0, 2.0f);
	DrawDebugSphere(GetWorld(), CastCrossHairLineTrace(GetOwner(), FocusingMaxDistance).ImpactPoint, FocusingRadiusExtent, 16, FColor::Cyan, false, -1.0f, 0, 2.0f);
}

const TArray<FHitResult> UFocusComponent::GetOverlappingActorsInFocusArea_Internal()
{
	TArray<FHitResult> Hits;
	TArray<FHitResult> ValidHits;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());

	const FVector& StartLoc = GetFocusRayCastStartLocation_Internal();
	const FVector& EndLoc = GetFocusRayCastEndLocation_Internal(StartLoc);

	const EDrawDebugTrace::Type DebugTrace = (bShowDebug) ? (EDrawDebugTrace::ForDuration) : 
	(EDrawDebugTrace::None);

	UKismetSystemLibrary::SphereTraceMulti(this, StartLoc, EndLoc, FocusingRadiusExtent, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), false, ActorsToIgnore, DebugTrace, Hits, true, FLinearColor::Red, FLinearColor::Green, GetWorld()->GetDeltaSeconds());

	if (Hits.Num() > 0)
	{
		for (auto& Hit : Hits)
		{
			const AActor* HitActor = Hit.Actor.Get();

			if (IsValid(HitActor))
			{
				ValidHits.Add(Hit);
			}
		}
	}

	return ValidHits;
}

const TWeakObjectPtr<AActor> UFocusComponent::FindBestFocusCandidate_Internal(const 
TArray<FHitResult>& ValidHits) const
{
	TWeakObjectPtr<AActor> Candidate;
	float BestDistance = 99999.0f;

	for (auto&& Hit : ValidHits)
	{
		const FVector& FocusActorLocation = Hit.ImpactPoint;

		//	If using the developer mode, ignore every setting and just focus on everything.
		if (!bDeveloperMode)
		{
			//	Whether or not to only focus on actors with the FocusableComponent and if they are focusable or not
			if (bFocusOnlyOnFocusables)
			{
				const FVector& FocusRelativeLocation = GetFocusDistanceRelativeLocation();
				const UFocusableComponent* FocusableComponent = Cast<UFocusableComponent>(Hit.Actor->GetComponentByClass(UFocusableComponent::StaticClass()));
				const float DistanceToActorWhoIsFocusing = (FocusRelativeLocation - 
				FocusActorLocation).Size();	//	Used for trimming results

				if (!IsValid(FocusableComponent) || !FocusableComponent->IsFocusable() || (DistanceToActorWhoIsFocusing > FocusableComponent->GetFocusDistance()))
				{
					continue;
				}
			}
		}

		const FVector& FocusRayStartLocation = GetFocusRayCastStartLocation_Internal();
		const FVector& FocusRayEndLocation = GetFocusRayCastEndLocation_Internal(FocusRayStartLocation);
		FVector&& NormVec1 = (FocusRayEndLocation - FocusRayStartLocation);
		FVector&& NormVec2 = (FocusActorLocation - FocusRayStartLocation);
		NormVec1.Normalize();
		NormVec2.Normalize();

		const float DotProduct = FVector::DotProduct(NormVec1, NormVec2);
		const float AngleToFocusActor = FMath::Acos(DotProduct);
		const float DistanceToFocusActorFromFocusStartPoint = (FocusActorLocation - 
		FocusRayStartLocation).Size();
		
		const float FocusActorDistanceToFocusCenterLine = DistanceToFocusActorFromFocusStartPoint * 
		(FMath::Sin(AngleToFocusActor));

		//	This actor is a better candidate
		if (FocusActorDistanceToFocusCenterLine < BestDistance)
		{
			Candidate = Hit.Actor;
			BestDistance = FocusActorDistanceToFocusCenterLine;
		}
	}

	return Candidate;
}

void UFocusComponent::UpdateFocusWorldLocation_Internal()
{
	const FHitResult& RV_Hit = CastCrossHairLineTrace(GetOwner(), FocusingMaxDistance);
	FocusWorldLocation = RV_Hit.ImpactPoint;
}

// Called every frame
void UFocusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateFocusedActor();

	bShowDebug = CVarShowFocusDebugs.GetValueOnGameThread() == 1 ? true : false;
	if ((bShowDebug) && !FocusWorldLocation.IsZero())
	{
		DrawDebugs(DeltaTime);
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFocusComponentModule, FocusComponent)