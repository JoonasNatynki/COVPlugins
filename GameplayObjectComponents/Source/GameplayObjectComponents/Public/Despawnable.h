#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include <ObjectAndNameAsStringProxyArchive.h>
#include <MemoryWriter.h>
#include "Despawnable.generated.h"

/*
Grabbed from: https://forums.unrealengine.com/development-discussion/c-gameplay-programming/88477-spawning-actors-from-serialized-data
*/

DECLARE_LOG_CATEGORY_EXTERN(LogDespawnable, Log, All)

USTRUCT(BlueprintType, Blueprintable)
struct FDespawnableRecord
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, SaveGame)
		UClass* Class;

	UPROPERTY(BlueprintReadWrite, SaveGame)
		TWeakObjectPtr<AActor> Owner;

	UPROPERTY(BlueprintReadWrite, SaveGame)
		TWeakObjectPtr<ULevel> OwningLevel;

	UPROPERTY(BlueprintReadWrite, SaveGame)
		FTransform Transform;

	UPROPERTY(BlueprintReadWrite, SaveGame)
		FString Name;

	//extra data for actor specific implementations
	UPROPERTY(BlueprintReadWrite, SaveGame)
		TArray<uint8> Data;

	//might be able to do an internal serialize here...
	FORCEINLINE FArchive& Serialize(FArchive& Ar)
	{
		Ar << Class;
		Ar << Transform;
		Ar << Name;
		Ar << Data;
		return Ar;
	}
};

UCLASS()
class UDespawnableSerializer : public UObject
{
	GENERATED_BODY()

public:
	UDespawnableSerializer() {};
	FDespawnableRecord Write(AActor* Owner);
	void Read(AActor* Owner, FDespawnableRecord& Data);

	//	The FArchive that will serialize and restore serialized data when needed. Will be nullptr when not in use
	FArchive* ReaderWriter;

	UFUNCTION(BlueprintCallable)
		bool IsRestoredState() const { return ReaderWriter->IsLoading(); };

	UFUNCTION(BlueprintCallable)
		void SerializeBoolean(UPARAM(ref) bool& Bool) { SerializeVariable(Bool); };

	UFUNCTION(BlueprintCallable)
		void SerializeInteger(UPARAM(ref) int32& Integer) { SerializeVariable(Integer); };

	UFUNCTION(BlueprintCallable)
		void SerializeFloat(UPARAM(ref) float& Float) { SerializeVariable(Float); };

	template<class T> void SerializeVariable(T& Variable)
	{
		ensure(ReaderWriter);
		*ReaderWriter << Variable;
	};
};

struct FDespawnableArchive : public FObjectAndNameAsStringProxyArchive
{
	FDespawnableArchive(FArchive& InInnerArchive, bool bInLoadIfFindFails)
		: FObjectAndNameAsStringProxyArchive(InInnerArchive, bInLoadIfFindFails)
	{
		ArIsSaveGame = true;
	}
};

// This class does not need to be modified.
UINTERFACE()
class UDespawnable : public UInterface
{
	GENERATED_BODY()
};

class GAMEPLAYOBJECTCOMPONENTS_API IDespawnable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void SerializeActor(UDespawnableSerializer* Serializer);

};
