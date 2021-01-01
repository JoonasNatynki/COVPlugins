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

#include "EngineUtils.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

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
				EndLoc = StartLocation + (OwnerCameraManagerActor->GetActorForwardVector() * FocusInternalMaxLimit);
				break;
			}
		case(EFocusMethod::MouseScreenPosition):
			{
				const APlayerController* PlayerController = TryGetPlayerController();
				FVector WorldLocation;
				FVector WorldDirection;
				PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
				EndLoc = WorldLocation + (WorldDirection * FocusInternalMaxLimit);
				break;
			}
		}
	}
	else
	{
		EndLoc = StartLoc + (GetOwner()->GetActorForwardVector() * FocusInternalMaxLimit);
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
		case(EFocusDistanceRelativeTo::PlayerPawnCapsuleBottom):
		{
			const APawn* Pawn = TryGetPlayerPawn();
			return Pawn->GetActorLocation() - FVector(0,0,Cast<ACharacter>(Pawn)->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
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
	const FVector& FocusingSourceLocation = GetFocusDistanceRelativeLocation();
	UWorld* World = GetWorld();
	//	Focus location crosshair
	DrawDebugCrosshairs(World, FocusWorldLocation, FRotator::ZeroRotator,50.0f, FColor::Red, false, -1.0f, 0);
	DrawDebugCrosshairs(World, FocusingSourceLocation, FRotator::ZeroRotator,50.0f, FColor::Red, false, -1.0f, 0);	
	//	Focusing point and its reach radius
	DrawDebugSphere(World, FocusWorldLocation, FocusingRadiusExtent, 16, FColor::Cyan, false, -1.0f, 0, 1.0f);
	//	The focusing source reach location
	//DrawDebugSphere(World, FocusingSourceLocation, FocusingMaxDistance, 16, FColor::Cyan, false, -1.0f, 0, 1.0f);

	//	Line and distance from focus source to focus world location
	const FColor ColorOfFocusSourceReachDistance = ((FocusingSourceLocation-FocusWorldLocation).Size() <= FocusingMaxDistance)?(FColor::Green):(FColor::Red);
	DrawDebugLine(World, FocusingSourceLocation, FocusWorldLocation, ColorOfFocusSourceReachDistance, false, -1.0f, 0, 1.0f);
	const FVector TextLocation = FocusingSourceLocation + ((FocusWorldLocation-FocusingSourceLocation)/2);
	DrawDebugString(World, TextLocation, FString::SanitizeFloat((FocusWorldLocation-FocusingSourceLocation).Size()), nullptr, ColorOfFocusSourceReachDistance, deltaTime, true, 1);
	
	//	Draw every focusable actor possible focus reach radius
	for(FActorIterator ActorIter(World); ActorIter; ++ActorIter)
	{
		if(UFocusableComponent* FocusComp = ActorIter->FindComponentByClass<UFocusableComponent>())
		{
			const FColor ColorOfFocusableReachRadius = ((FocusingSourceLocation-ActorIter->GetActorLocation()).Size() <= FocusComp->GetFocusDistance() || *ActorIter == GetFocusedActor())?(FColor::Green):(FColor::Red);
			DrawDebugLine(World, ActorIter->GetActorLocation(), ActorIter->GetActorLocation()+ FVector(0,0, FocusComp->GetFocusDistance()), ColorOfFocusableReachRadius, false, -1.0f, 0, 2.0f);
			DrawDebugSphere(World, ActorIter->GetActorLocation(), FocusComp->GetFocusDistance(), 6, ColorOfFocusableReachRadius, false, -1.0f, 0, 1.0f);
		}
	}
}

const TArray<FHitResult> UFocusComponent::GetOverlappingActorsInFocusArea_Internal()
{
	TArray<FHitResult> Hits;
	TArray<FHitResult> ValidHits;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());

	const FVector& StartLoc = GetFocusRayCastStartLocation_Internal();
	const FVector& EndLoc = GetFocusRayCastEndLocation_Internal(StartLoc);

	const EDrawDebugTrace::Type DebugTrace = (false) ? (EDrawDebugTrace::ForDuration) : 
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

const TWeakObjectPtr<AActor> UFocusComponent::FindBestFocusCandidate_Internal(const TArray<FHitResult>& ValidHits) const
{
	TWeakObjectPtr<AActor> Candidate;
	float BestDistance = FocusInternalMaxLimit;

	for (auto&& Hit : ValidHits)
	{
		const FVector& FocusActorLocation = Hit.ImpactPoint;

		//	Whether or not to only focus on actors with the FocusableComponent and if they are focusable or not
		if (bFocusOnlyOnFocusables)
		{
			const FVector& FocusSourceLocation = GetFocusDistanceRelativeLocation();
			const UFocusableComponent* FocusableComponent = Cast<UFocusableComponent>(Hit.Actor->GetComponentByClass(UFocusableComponent::StaticClass()));
			const float DistanceToActorWhoIsFocusing = (FocusSourceLocation - FocusActorLocation).Size();	//	Used for trimming results

			if (!IsValid(FocusableComponent) || !FocusableComponent->IsFocusable() || (DistanceToActorWhoIsFocusing > FocusableComponent->GetFocusDistance()) || (DistanceToActorWhoIsFocusing > FocusingMaxDistance))
			{
				continue;
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
		
		const float FocusActorDistanceToFocusCenterLine = DistanceToFocusActorFromFocusStartPoint * (FMath::Sin(AngleToFocusActor));

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
	const FHitResult& RV_Hit = CastCrossHairLineTrace(GetOwner(), FocusInternalMaxLimit);
	FocusWorldLocation = RV_Hit.ImpactPoint;
}

FHitResult UFocusComponent::CastCrossHairLineTrace(const AActor* Character, float 
RayDistance) const
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
				ControllerForwardVector = WorldDirection;
			}
		}

		RV_Hit = SimpleTraceByChannel
        (
            Character,
            PlayerViewWorldLocation,
            PlayerViewWorldLocation + (ControllerForwardVector * RayDistance),
            ECollisionChannel::ECC_Camera,
            FName("AimTrace")
        );

		return RV_Hit;
	}

	return RV_Hit;
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