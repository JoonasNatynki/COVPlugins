// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UE4Helpers.generated.h"

class FUE4HelpersModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

class FAssetRegistryModule;
class APlayerCameraManager;

DECLARE_LOG_CATEGORY_EXTERN(LogUE4Helpers, Log, All)

//	MACROS	#####################################################################################################################
#define PRINT_FUNCTION *FString(__FUNCTION__).Append(":(").Append(FString::FormatAsNumber(__LINE__)).Append("): ")

#define IS_SERVER GetNetMode() == ENetMode::NM_DedicatedServer || GetNetMode() == ENetMode::NM_ListenServer
#define IS_DEDICATED_SERVER GetNetMode() == ENetMode::NM_DedicatedServer

//#define XYZLOG(category, log category, msg, ...) UE_LOG(category, log category, TEXT("%s: %s"), PRINT_FUNCTION, TEXT(msg), ##__VA_ARGS__)

#define IS_NOT_LOCALLY_CONTROLLED_WARNING if(!IsLocallyControlled()){UE_LOG(LogTemp, Warning, TEXT("%s: Should a non-client be calling this function?"), PRINT_FUNCTION)}

#define COV_LOG(_namespace, _logcategory, _text, ...) \
{\
const FString appendText = FString::Printf(_text, ##__VA_ARGS__);\
const FString netModePrefix = UE4CodeHelpers::GetNetModePrefix(this);\
UE_LOG(_namespace, _logcategory, TEXT("%s%s%s"), *netModePrefix, PRINT_FUNCTION, *appendText);\
}


#define GET_AND_CACHE_COMPONENT(_componentclass, _containervariablename)\
{\
	_componentclass* tempComp = nullptr;\
	TSet<UActorComponent*> comps = GetComponents();\
	for (auto & comp : comps)\
	{\
		tempComp = Cast<_componentclass>(comp);\
		if (tempComp)\
		{\
			_containervariablename = tempComp;\
			break;\
		}\
	}\
	if(!ensureMsgf(tempComp, TEXT("%s Component was not found."), *FString(#_componentclass)))\
	{\
	FMessageLog("PIE").Warning(FText::Format(NSLOCTEXT("UE4CodeHelpers", "Help", "No {0} found in "), FText::FromString(FString(#_componentclass))))->AddToken(FUObjectToken::Create(this));\
	}\
}\

#define GET_AND_STORE_COMPONENT_FROM_COMPONENT(_componentclass, _containervariablename) {\
_componentclass* tempComp = nullptr;\
TSet<UActorComponent*> comps = GetOwner()->GetComponents();\
for (auto & comp : comps)\
{\
	tempComp = Cast<_componentclass>(comp);\
	if (tempComp)\
	{\
		_containervariablename = tempComp;\
		break;\
	}\
}\
ensureMsgf(tempComp != nullptr, TEXT("##_componentclass Component was not found! Please add it as a component to this actor or the actor won't work properly!"));\
}\

//	BEGINNING OF USE INTERFACE MAKRO	###############################################################################
#define USE_INTERFACE(_objectwithinterface, _interface, _functionname, ...) TWeakObjectPtr<UObject> interfaceObject = _objectwithinterface;\
if (interfaceObject.IsValid())\
{\
	if (interfaceObject->GetClass()->ImplementsInterface(U##_interface::StaticClass()))\
	{\
		I##_interface::Execute_##_functionname(interfaceObject.Get(), ##__VA_ARGS__);\
	}\
	else\
	{\
		UE_LOG(LogTemp, Log, TEXT("Using interface failed! The object (%s) does not implement such."), *GetNameSafe(_objectwithinterface));\
	}\
}\
//	END OF USING INTERFACE MAKRO	###################################################################################
//	#####################################################################################################################

#define SIMPLE_DELAY(_funcDef, rate, bLooping, firstDelay)\
FTimerHandle smallDelay;\
FTimerDelegate timerCallback;\
timerCallback.BindLambda([&]\
{\
	_funcDef\
});\
GetWorld()->GetTimerManager().SetTimer(smallDelay, timerCallback, rate, bLooping, firstDelay);\

template<typename T>
static FString EnumToString(const FString& enumName, const T value)
{
	UEnum* pEnum = FindObject<UEnum>(ANY_PACKAGE, *enumName);
	return *(pEnum ? pEnum->GetNameStringByIndex(static_cast<uint8>(value)) : "null");
}

DECLARE_DYNAMIC_DELEGATE_OneParam(FAsyncChildClassLoadSignature, const UClass*, AsyncLoadedClassType);

//	Blueprint function library class
UCLASS()
class UE4HELPERS_API UE4CodeHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UE4CodeHelpers(const FObjectInitializer& ObjInit);

	UFUNCTION(Category = "UEHelperFunctions", BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static FString GetNetModePrefix(const UObject* WorldContextObject);

	//	Simplified line trace function with a baked in Trace Parameter initialization
	UFUNCTION(Category = "UEHelperFunctions", BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static FHitResult SimpleTraceByChannel(const UObject* WorldContextObject, const FVector& startPos, const FVector& endPos, ECollisionChannel channel, const FName& TraceTag);

	UFUNCTION(Category = "UEHelperFunctions", BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static UActorComponent* FindComponentByInterface(const AActor* Actor, TSubclassOf<UInterface> Interface);

	template <class T> static T* FindComponentByIInterface(const UActorComponent* Comp);

	template <class T> static T* FindComponentByIInterface(const AActor* Actor);
	
	UFUNCTION(Category = "UEHelperFunctions", BlueprintCallable)
	//	A simplified line tracer for getting a hit on your cross hairs
	static FHitResult CastCrossHairLineTrace(const AActor* character, float rayDistance);

	UFUNCTION(Category = "UEHelperFunctions", BlueprintCallable)
	//	Will read a file in a specific folder with the variable name
	static FString GetFileLine(const FString& InFileName, const FString& Folder, const FString& ConfigName);

	UFUNCTION(Category = "UEHelperFunctions", BlueprintCallable)
	//	Will read a file's variable's value in the config folder
	static FString GetConfigFileLine(const FString& InFileName, const FString& ConfigName);

	UFUNCTION(Category = "UEHelperFunctions", BlueprintCallable)
	//	Will return the number of lines in a file. No file found = -1
	static int32 GetNumberOfRowsInFile(const FString& InFileName, const FString& Folder);

	UFUNCTION(Category = "UEHelperFunctions", BlueprintCallable, BlueprintPure)
	//	Will return the number of commits in a the repository. No repository found = -1
	static int32 GetRepositoryCommitCount();

	UFUNCTION(Category = "UEHelperFunctions", BlueprintCallable)
	static APlayerCameraManager* TryGetPawnCameraManager(const APawn* pawn);

	UFUNCTION(Category = "UEHelperFunctions", BlueprintCallable)
	//	Simply checks if the object is of type or not
	static bool IsOfType(const UObject* object, TSubclassOf<UObject> type);

	UFUNCTION(Category = "UEHelperFunctions", BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static TArray<FVector> CalculateParabolicTrajectory(const UObject* WorldContextObject, const FVector& StartLocation, const FVector& Velocity, const FVector& Gravity, const float TimeToSimulate, const int32 NumberOfTrajectoryPoints);


	static FString GetNetModeName(const UObject* worldContextObject);


	UFUNCTION(BlueprintCallable, BlueprintPure, CustomThunk, meta = (DisplayName = "Is array empty", CompactNodeTitle = "ISEMPTY", ArrayParm = "TargetArray"), Category = "Utilities|Array")
	static bool IsArrayEmpty(const TArray<int32>& TargetArray);

	UFUNCTION(Category = "UEHelperFunctions", BlueprintCallable)
	//	Calculates a rotator that has its up vector pointing to the normal given. Very useful for things that need to stick to surfaces like bullet decals and footprints
	static FRotator OrientRotationToNormalVector(const FRotator& CurrentRotation, const FVector& Normal);

	UFUNCTION(Category = "UEHelperFunctions", BlueprintCallable)
	//	A more lightweight version of the GetAllChildClassesOfType. This will only search the classes that are already loaded in memory.
	static TArray<UClass*> GetAllAssetsOfType(TSubclassOf<AActor> Type, const FString& PathToSearchFor);

	UFUNCTION(Category = "UEHelperFunctions", BlueprintCallable)
	//	Rotates a vector around a point
	static FVector RotateVectorAroundPoint(const FVector& vectorToRotate, const FVector& pointToRotateAround, const FRotator& theRotationToApply);

	template<class T> static T* FindDefaultComponentsByClass(const TSubclassOf<AActor> InActorClass, const TSubclassOf<T> InComponentClass);

	static bool GenericIsArrayEmpty(void* TargetArray, const FArrayProperty* ArrayProp);

	DECLARE_FUNCTION(execIsArrayEmpty)
	{
		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<FArrayProperty>(NULL);
		void* ArrayAddr = Stack.MostRecentPropertyAddress;
		FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Stack.MostRecentProperty);
		if (!ArrayProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}

		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)RESULT_PARAM = GenericIsArrayEmpty(ArrayAddr, ArrayProperty);
		P_NATIVE_END;
	}


	static FORCEINLINE bool SimpleTraceSphere(
		AActor* ActorToIgnore,
		const FVector& Start,
		const FVector& End,
		const float Radius,
		FHitResult& HitOut,
		ECollisionChannel TraceChannel = ECC_Pawn
	);
};

template <class T>
T* UE4CodeHelpers::FindComponentByIInterface(const UActorComponent* Comp)
{
	return Comp ? FindComponentByIInterface<T>(Comp->GetOwner()) : nullptr;
}

template <class T>
T* UE4CodeHelpers::FindComponentByIInterface(const AActor* Actor)
{
	if (!IsValid(Actor))
	{
		return nullptr;
	}

	TInlineComponentArray<UActorComponent*> Comps(Actor);

	for (UActorComponent* Comp : Comps)
	{
		T* InterfaceComp = Cast<T>(Comp);
		if (InterfaceComp)
		{
			return InterfaceComp;
		}
	}

	return nullptr;
}

template<class T> T* UE4CodeHelpers::FindDefaultComponentsByClass(const TSubclassOf<AActor> InActorClass, const TSubclassOf<T> InComponentClass)
{
	if (!IsValid(InActorClass))
	{
		return nullptr;
	}
 
	// Check CDO.
	AActor* ActorCDO = InActorClass->GetDefaultObject<AActor>();
	T* FoundComponent = ActorCDO->FindComponentByClass<T>();
 
	if (FoundComponent != nullptr)
	{
		return FoundComponent;
	}
 
	// Check blueprint nodes. Components added in blueprint editor only (and not in code) are not available from
	// CDO.
	UBlueprintGeneratedClass* RootBlueprintGeneratedClass = Cast<UBlueprintGeneratedClass>(InActorClass);
	UClass* ActorClass = InActorClass;
 
	// Go down the inheritance tree to find nodes that were added to parent blueprints of our blueprint graph.
	do
	{
		UBlueprintGeneratedClass* ActorBlueprintGeneratedClass = Cast<UBlueprintGeneratedClass>(ActorClass);
		if (!ActorBlueprintGeneratedClass)
		{
			return nullptr;
		}
 
		const TArray<USCS_Node*>& ActorBlueprintNodes =
            ActorBlueprintGeneratedClass->SimpleConstructionScript->GetAllNodes();
 
		for (USCS_Node* Node : ActorBlueprintNodes)
		{
			if (Node->ComponentClass->IsChildOf(InComponentClass))
			{
				return Cast<T>(Node->GetActualComponentTemplate(RootBlueprintGeneratedClass));
			}
		}
 
		ActorClass = Cast<UClass>(ActorClass->GetSuperStruct());
 
	} while (ActorClass != AActor::StaticClass());
 
	return nullptr;
}

FORCEINLINE bool UE4CodeHelpers::SimpleTraceSphere(
	AActor* ActorToIgnore,
	const FVector& Start,
	const FVector& End,
	const float Radius,
	FHitResult& HitOut,
	ECollisionChannel TraceChannel
) {
	FCollisionQueryParams TraceParams(FName(TEXT("SimpleTraceSphere")), true, ActorToIgnore);
	TraceParams.bTraceComplex = true;
	//TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = false;

	//Ignore Actors
	TraceParams.AddIgnoredActor(ActorToIgnore);

	//Re-initialize hit info
	HitOut = FHitResult(ForceInit);

	//Get World Source
	TObjectIterator<APlayerController> ThePC;
	if (!ThePC) return false;


	return ThePC->GetWorld()->SweepSingleByChannel(
		HitOut,
		Start,
		End,
		FQuat(),
		TraceChannel,
		FCollisionShape::MakeSphere(Radius),
		TraceParams
	);
}


FORCEINLINE FHitResult UE4CodeHelpers::SimpleTraceByChannel(const UObject* inObj, const FVector& startPos, const FVector& endPos, ECollisionChannel channel, const FName& TraceTag)
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

FORCEINLINE FHitResult UE4CodeHelpers::CastCrossHairLineTrace(const AActor* character, float rayDistance)
{
	FHitResult RV_Hit(ForceInit);
	const APawn* pawn = Cast<APawn>(character);

	if (!ensureMsgf(IsValid(pawn), TEXT("Could not cast crosshair line trace. The actor wasn't a pawn or the pawn wasn't valid anymore.")))
	{
		return RV_Hit;
	}

	AActor* pawnCameraManager = Cast<AActor>(TryGetPawnCameraManager(pawn));

	if (IsValid(pawnCameraManager))
	{

		//	Ray starting point
		FVector playerViewWorldLocation = pawnCameraManager->GetActorLocation();
		//	end point target direction

		FVector controllerForwardVector = pawnCameraManager->GetActorForwardVector();

		RV_Hit = UE4CodeHelpers::SimpleTraceByChannel
		(
			character,
			playerViewWorldLocation + (controllerForwardVector),
			playerViewWorldLocation + (controllerForwardVector * rayDistance),
			ECollisionChannel::ECC_Camera,
			FName("AimTrace")
		);

		return RV_Hit;
	}

	return RV_Hit;
}
