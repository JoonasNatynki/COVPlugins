#include "DespawnableActor.h"
#include "Despawnable.h"

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

void UDespawnableActor::RestoreActorState(FDespawnableRecord& Data)
{
	UDespawnableSerializer* Reader = NewObject<UDespawnableSerializer>(this, UDespawnableSerializer::StaticClass());
	Reader->Read(GetOwner(), Data);
	Reader->ConditionalBeginDestroy();
}

