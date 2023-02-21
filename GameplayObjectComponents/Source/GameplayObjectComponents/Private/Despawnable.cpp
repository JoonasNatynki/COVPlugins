#include "Despawnable.h"

DEFINE_LOG_CATEGORY(LogDespawnable)

FDespawnableRecord UDespawnableSerializer::Write(AActor* Owner)
{
	UE_LOG(LogDespawnable, Error, TEXT("Creating respawn data for actor (%s)."), *GetNameSafe(Owner));

	ensure(IsValid(Owner));

	FDespawnableRecord Record = FDespawnableRecord();
	Record.Class = Owner->GetClass();
	Record.Name = Owner->GetName();
	Record.Transform = Owner->GetActorTransform();
	Record.Owner = Owner->GetOwner();
	Record.OwningLevel = Owner->GetTypedOuter<ULevel>();

	FMemoryWriter Wri = FMemoryWriter(Record.Data);
	ReaderWriter = &Wri;
	ReaderWriter->ArIsSaveGame = true;

	IDespawnable::Execute_SerializeActor(Owner, this);
	ReaderWriter = nullptr;

	return Record;
}

void UDespawnableSerializer::Read(AActor* Owner, FDespawnableRecord& Data)
{
	ensureMsgf(Owner->IsA(Data.Class), TEXT("Types are incompatible. The actor restoring its data NEEDS to be of same type or inherit from the type that is stored in the data. Types are (%s, %s)"), *Owner->GetClass()->GetName(), *Data.Class->GetName());
	FMemoryReader Reader = FMemoryReader(Data.Data);
	ReaderWriter = &Reader;

	//	Restore the data
	IDespawnable::Execute_SerializeActor(Owner, this);
	ReaderWriter = nullptr;
}
