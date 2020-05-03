#include "Despawnable.h"
#include <GameFramework/Actor.h>
#include <MemoryReader.h>

FDespawnableRecord UDespawnableSerializer::Write(AActor* Owner)
{
	UE_LOG(LogTemp, Error, TEXT("Creating respawn data for actor (%s)."), *GetNameSafe(Owner));

	ensure(IsValid(Owner));

	FDespawnableRecord Record = FDespawnableRecord();
	Record.Class = Owner->GetClass();
	Record.Name = Owner->GetName();
	Record.Transform = Owner->GetActorTransform();

	FMemoryWriter Wri = FMemoryWriter(Record.Data);
	ReaderWriter = &Wri;
	ReaderWriter->ArIsSaveGame = true;

	IDespawnable::Execute_SerializeActor(Owner, this);
	ReaderWriter = nullptr;

	return Record;
}

void UDespawnableSerializer::Read(AActor* Owner, FDespawnableRecord& Data)
{
	FMemoryReader Reader = FMemoryReader(Data.Data);
	ReaderWriter = &Reader;

	IDespawnable::Execute_SerializeActor(Owner, this);
	ReaderWriter = nullptr;
}
