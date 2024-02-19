// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UE4Helpers.h"
#include "Engine.h"

#if WITH_EDITOR

#endif

#include "Misc/UObjectToken.h"
#include "UObject/UnrealTypePrivate.h"

#define LOCTEXT_NAMESPACE "UE4CodeHelpers"

DEFINE_LOG_CATEGORY(LogUE4Helpers)

void FUE4HelpersModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FUE4HelpersModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

UE4CodeHelpers::UE4CodeHelpers(const FObjectInitializer& ObjInit) : Super(ObjInit)
{

}

static TAutoConsoleVariable<int32> CVarShowBarabolicTrajectoryCalculationDebugLine(TEXT("UE4CodeHelpers.ShowBarabolicTrajectoryCalculationDebugs"),
	0,
	TEXT("Show barabolic trajectory calculation debugs."));


FString UE4CodeHelpers::GetNetModePrefix(const UObject* WorldContextObject)
{
	FString netModePrefix = GetNetModeName(WorldContextObject);
	return netModePrefix.IsEmpty() ? TEXT("") : FString::Printf(TEXT("%s: "), *netModePrefix);
}

UActorComponent* UE4CodeHelpers::FindComponentByInterface(const AActor* Actor, TSubclassOf<UInterface> Interface)
{
	if (!IsValid(Actor))
	{
		return nullptr;
	}

	const TInlineComponentArray<UActorComponent*> Comps(Actor);

	for (UActorComponent* Comp : Comps)
	{
		if (Comp->GetClass()->ImplementsInterface(Interface))
		{
			return Comp;
		}
	}

	return nullptr;
}

bool UE4CodeHelpers::IsOfType(const UObject* object, TSubclassOf<UObject> type)
{
	return object->IsA(type);
}

TArray<FVector> UE4CodeHelpers::CalculateParabolicTrajectory(const UObject* WorldContextObject, const FVector& StartLocation, const FVector& Velocity, const FVector& Gravity, const float TimeToSimulate, const int32 NumberOfTrajectoryPoints)
{
	TArray<FVector> TrajectoryPathPoints;
	float velocityFloat = Velocity.Size();
	for (int x = 0; x < NumberOfTrajectoryPoints; x++)
	{
		FVector TempPoint;
		FVector Offset;
		//  First point, no calculation
		if (x == 0)
		{
			TempPoint = StartLocation;
			TrajectoryPathPoints.Add(TempPoint);
		}
		else
		{
			const float Time = (TimeToSimulate / NumberOfTrajectoryPoints) * (x);
			Offset = (Gravity * (Time * Time));
			TempPoint = (StartLocation + (Velocity * Time)) + Offset;
			TrajectoryPathPoints.Add(TempPoint);
		}
		if (CVarShowBarabolicTrajectoryCalculationDebugLine.GetValueOnGameThread() == 1)
		{
			//  Draw the sample points
			UKismetSystemLibrary::DrawDebugPoint(WorldContextObject->GetWorld(), TempPoint, 15.0f, FLinearColor::Red, 10.0f);
			//  Draw lines between points
			if ((x > 0))
			{
				UKismetSystemLibrary::DrawDebugLine(WorldContextObject->GetWorld(), TempPoint, TrajectoryPathPoints[x - 1], FLinearColor::Green, 10.0f, 5.0f);
			}
		}
	}
	return TrajectoryPathPoints;
}

FString UE4CodeHelpers::GetFileLine(const FString& InFileName, const FString& Folder, const FString& ConfigName)
{
	TArray<FString> Rows;
	const FString FilePath = FString(FPaths::ProjectDir()).Append(Folder).Append(InFileName);
	const bool FoundSomething = FFileHelper::LoadFileToStringArray(Rows, *FilePath);

	if (ensure(FoundSomething))
	{
		UE_LOG(LogUE4Helpers, Log, TEXT("Found a file with the name (%s). Processing words to locate the setting for configuration (%s)."), *InFileName, *ConfigName);

		for (auto&& Row : Rows)
		{
			const bool ContainsString = Row.Contains(ConfigName, ESearchCase::IgnoreCase, 
			ESearchDir::FromStart);

			if (ContainsString)
			{
				TArray<FString> ParsedLine;
				Row.ParseIntoArray(ParsedLine, TEXT("="), true);
				const int32 ParsedArrayLength = ParsedLine.Num();
				FString& ValueFound = ParsedLine[ParsedArrayLength - 1];
				//	Remove spaces if any
				ValueFound.RemoveFromStart(" ");

				UE_LOG(LogUE4Helpers, Log, TEXT("Configuration (%s) found with the value of (%s)"), *ConfigName, *ValueFound);
				return ParsedLine[ParsedArrayLength - 1];
			}
		}
		UE_LOG(LogUE4Helpers, Error, TEXT("No line (%s) was found�in the config file (%s)."), *ConfigName, *InFileName);

		return FString(TEXT(""));
	}
	else
	{
		UE_LOG(LogUE4Helpers, Error, TEXT("Did not find a file named (%s)."), *InFileName);
		FMessageLog("PIE").Error(FText::Format(LOCTEXT("COVBlueprintFunctionLibrary", "Could not find a file named ({0})."), FText::FromString(InFileName)));
		return FString(TEXT(""));
	}
}

FString UE4CodeHelpers::GetConfigFileLine(const FString& InFileName, const FString& ConfigName)
{
	return GetFileLine(InFileName, FString(TEXT("/Config/")), ConfigName);
}

int32 UE4CodeHelpers::GetNumberOfRowsInFile(const FString& InFileName, const FString& Folder)
{
	TArray<FString> Rows;
	const FString FilePath = FString(FPaths::ProjectDir()).Append(Folder).Append(InFileName);
	const bool FoundSomething = FFileHelper::LoadANSITextFileToStrings(*FilePath, nullptr, Rows);

	if (FoundSomething)
	{
		const int32 RowCount = Rows.Num();
		UE_LOG(LogUE4Helpers, Verbose, TEXT("Found a number of (%d) rows in the file (%s)."), RowCount, *InFileName);
		return RowCount;
	}

	UE_LOG(LogUE4Helpers, Error, TEXT("Could not read the number of lines in a file (%s). No file found!"), *InFileName);
	FMessageLog("PIE").Error(FText::Format(LOCTEXT("UE4CodeHelpers", "Could not read the number of lines in a file ({0}). No file found!."), FText::FromString(InFileName)));

	return -1;
}

int32 UE4CodeHelpers::GetRepositoryCommitCount()
{
	const int32& NumberOfCommits = static_cast<int32>(GetNumberOfRowsInFile(FString(TEXT("HEAD")),
	FString(TEXT("/.git/logs/"))));

	if (NumberOfCommits == -1)
	{
		UE_LOG(LogUE4Helpers, Error, TEXT("No git repository folder found. Could not find the number of commits."));
		FMessageLog("PIE").Error(FText::FromString("No git repository folder found. Could not find the number of commits."));
		return -1;
	}

	return NumberOfCommits;
}

APlayerCameraManager* UE4CodeHelpers::TryGetPawnCameraManager(const APawn* pawn)
{
	if (!ensureMsgf(IsValid(pawn), TEXT("The pawn wasn't valid anymore.")))
	{
		FMessageLog("PIE").Error(FText::FromString("Could not get pawn camera manager. Pawn wasn't valid."));
		return nullptr;
	}
	AController* temp = pawn->GetController();
	APlayerController* playerController = Cast<APlayerController>(pawn->GetController());

	if (!IsValid(playerController))
	{
		//FMessageLog("PIE").Error(FText::FromString("Could not get pawn camera manager. The pawn's controller was not valid."))->AddToken(FUObjectToken::Create(pawn));
		return nullptr;
	}


	if (!ensureMsgf(IsValid(playerController->PlayerCameraManager), TEXT("The player camera manager was not valid.")))
	{
		FMessageLog("PIE").Error(FText::FromString("Could not get pawn camera manager. The camera manager was not valid for pawn."))->AddToken(FUObjectToken::Create(pawn));
		return nullptr;
	}

	return playerController->PlayerCameraManager;
}

FString UE4CodeHelpers::GetNetModeName(const UObject* worldContextObject)
{
	FString result;

	if (UWorld* world = GEngine->GetWorldFromContextObject(worldContextObject, EGetWorldErrorMode::ReturnNull))
	{
		// Minus one to match the engine.
		int32 client_id = -1;

#if WITH_EDITOR
		if (world->WorldType == EWorldType::PIE)
		{
			client_id = GPlayInEditorID;

			const TIndirectArray<FWorldContext>& contexts = GEngine->GetWorldContexts();

			for (int32 i = 0, icount = contexts.Num(); i < icount; ++i)
			{
				if (contexts[i].World() == world)
				{
					client_id = contexts[i].PIEInstance;
					break;
				}
			}
		}
#endif

		switch (world->GetNetMode())
		{
		case NM_Client:
			result = FString::Printf(TEXT("Client %d"), client_id - 1);
			break;
		case NM_DedicatedServer:
		case NM_ListenServer:
			result = TEXT("Server");
			break;
		case NM_Standalone:
			break;
		}
	}

	return result;
}

FRotator UE4CodeHelpers::OrientRotationToNormalVector(const FRotator& CurrentRotation, const FVector& Normal)
{
	const FQuat RootQuat = CurrentRotation.Quaternion();
	const FVector UpVector = RootQuat.GetUpVector();
	FVector RotationAxis = FVector::CrossProduct(UpVector, Normal);
	RotationAxis.Normalize();

	const float DotProduct = FVector::DotProduct(UpVector, Normal);
	const float RotationAngle = FMath::Acos(DotProduct);

	const FQuat Quat = FQuat(RotationAxis, RotationAngle);

	const FQuat NewQuat = Quat * RootQuat;

	return NewQuat.Rotator();
}

TArray<UClass*> UE4CodeHelpers::GetAllAssetsOfType(TSubclassOf<AActor> Type, const FString& PathToSearchFor)
{
	UE_LOG(LogUE4Helpers, Log, TEXT("Getting all assets of type (%s) from path('%s')."), *GetNameSafe(Type->GetClass()), *PathToSearchFor);

	TArray<UClass*> Into;

	UObjectLibrary* Items = UObjectLibrary::CreateLibrary(Type, true, GIsEditor);
	Items->AddToRoot();
	Items->LoadBlueprintsFromPath(PathToSearchFor);

	TArray<UBlueprintGeneratedClass*> classes;
	Items->GetObjects<UBlueprintGeneratedClass>(classes);

	for (int32 i = 0; i < classes.Num(); ++i) {
		UBlueprintGeneratedClass* item = classes[i];
		const FString& Name = item->GetName();
		const FString& Path = item->GetPathName();

		//skip editor debug stuff...
		if (Name.StartsWith(TEXT("SKEL_"))) continue;

		UE_LOG(LogUE4Helpers, Warning, TEXT("- found / `%s` / in `%s`"), *Name, *Path);

		//:note: you can use ContainsByPredicate instead for more nuance
		Into.AddUnique(item);

	} //for each generated class

	return Into;
}

FVector UE4CodeHelpers::RotateVectorAroundPoint(const FVector& vectorToRotate, const FVector& pointToRotateAround, const FRotator& theRotationToApply)
{
	FVector translatedVector = vectorToRotate - pointToRotateAround;
	translatedVector = theRotationToApply.RotateVector(translatedVector);
	translatedVector = pointToRotateAround + translatedVector;

	return translatedVector;
}

const FVector UE4CodeHelpers::FindRandomPointInsideShapeComponent(const UShapeComponent* ShapeComponent)
{
	if (!ensureAlways(IsValid(ShapeComponent)))
	{
		FVector();
	}

	if (const UBoxComponent* AsBox = Cast<UBoxComponent>(ShapeComponent))
	{
		const FVector Center = AsBox->GetComponentLocation();
		const FVector Extent = AsBox->GetScaledBoxExtent();

		// Generate random point within the box
		const float RandX = FMath::RandRange(-Extent.X, Extent.X);
		const float RandY = FMath::RandRange(-Extent.Y, Extent.Y);
		const float RandZ = FMath::RandRange(-Extent.Z, Extent.Z);

		// Adjust for the box's rotation
		const FVector RandomPoint = Center + AsBox->GetComponentQuat().RotateVector(FVector(RandX, RandY, RandZ));
		return RandomPoint;
	}
	
	if (const USphereComponent* AsSphere = Cast<USphereComponent>(ShapeComponent))
	{
		const float Radius = AsSphere->GetScaledSphereRadius();
		const FVector Center = AsSphere->GetComponentLocation();

		const float RandTheta = FMath::RandRange(0.0f, 2.0f * PI);
		const float RandPhi = FMath::RandRange(0.0f, PI);
		const float RandRadius = FMath::RandRange(0.0f, Radius);

		// Convert spherical to Cartesian coordinates
		const float X = RandRadius * FMath::Sin(RandPhi) * FMath::Cos(RandTheta);
		const float Y = RandRadius * FMath::Sin(RandPhi) * FMath::Sin(RandTheta);
		const float Z = RandRadius * FMath::Cos(RandPhi);

		const FVector RandomPoint = Center + FVector(X, Y, Z);

		return RandomPoint;
	}

	ensureAlwaysMsgf(false, TEXT("Unhandled shape component."));

	return FVector();
}

bool UE4CodeHelpers::GenericIsArrayEmpty(void* TargetArray, const FArrayProperty* ArrayProp)
{
	if (TargetArray)
	{
		const FScriptArrayHelper ArrayHelper(ArrayProp, TargetArray);

		if (ArrayHelper.Num() == 0)
		{
			return true;
		}
	}

	return false;
}

IMPLEMENT_MODULE(FUE4HelpersModule, UE4Helpers)