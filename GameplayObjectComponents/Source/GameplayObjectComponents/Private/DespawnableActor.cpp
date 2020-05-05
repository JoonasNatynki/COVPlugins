#include "DespawnableActor.h"
#include "Despawnable.h"
#include <Engine/World.h>

DEFINE_LOG_CATEGORY(LogDespawnableActor)

UDespawnableActor::UDespawnableActor()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UDespawnableActor::BeginPlay()
{
	Super::BeginPlay();	
}

void UDespawnableActor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FDespawnableRecord UDespawnableActor::GetActorState()
{
	UDespawnableSerializer* Writer = NewObject<UDespawnableSerializer>(this, UDespawnableSerializer::StaticClass());
	FDespawnableRecord Rec = Writer->Write(GetOwner());
	Writer->ConditionalBeginDestroy();
	return Rec;
}

void UDespawnableActor::RestoreActorState(AActor* ActorToRestore, FDespawnableRecord Data)
{
	UDespawnableSerializer* Reader = NewObject<UDespawnableSerializer>(ActorToRestore, UDespawnableSerializer::StaticClass());
	Reader->Read(ActorToRestore, Data);
	Reader->ConditionalBeginDestroy();
}

AActor* UDespawnableActor::RespawnActorFromState(const UObject* WorldContextObject, FDespawnableRecord Data)
{
	ensure(IsValid(WorldContextObject));
	UWorld* World = WorldContextObject->GetWorld();
	if (IsValid(World))
	{
		UE_LOG(LogDespawnableActor, Log, TEXT("Beginning respawning actor of type (%s)..."), *Data.Class->GetName());

		const FTransform& Trans = Data.Transform;
		TSubclassOf<AActor> Class = TSubclassOf<AActor>(Data.Class);
		AActor* SpawnedActor = World->SpawnActorDeferred<AActor>(Class, Trans, Data.Owner.Get(), nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		if (ensure(IsValid(SpawnedActor)))
		{
			//	Do other initialization here...
			UDespawnableActor::RestoreActorState(SpawnedActor, Data);
			SpawnedActor->FinishSpawning(Trans, true);
			UE_LOG(LogDespawnableActor, Log, TEXT("...Actor of type (%s) was successfully respawned."), *Data.Class->GetName());

			return SpawnedActor;
		}
		else
		{
			UE_LOG(LogDespawnableActor, Warning, TEXT("...Actor of type (%s) was NOT successfully respawned."), *Data.Class->GetName());
		}
	}

	return nullptr;
}

