// Fill out your copyright notice in the Description page of Project Settings.

#include "MetadataModifiers.h"
#include <typeinfo>
#include <string>

DEFINE_LOG_CATEGORY(LogMetaModifiers)

// Sets default values for this component's properties
UMetadataModifiers::UMetadataModifiers()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

const TArray<FMetaModifierProperty> UMetadataModifiers::GetMetaModifiersByName(const FName& InMetaModifierName) const
{
	TArray<FMetaModifierProperty> foundModifiers;

	if (!ensure(!InMetaModifierName.IsNone()))
	{
		return foundModifiers;
	}

	for (auto& metaMod : MetaModifiers)
	{
		if (metaMod.MetaModifierName == InMetaModifierName)
		{
			foundModifiers.Add(metaMod);
		}
	}

	return foundModifiers;
}

float UMetadataModifiers::GetMetaModifierValue_Float(const FName& metaModifierName)
{
	return GetMetamodifierValue<float>(metaModifierName);
}

int32 UMetadataModifiers::GetMetaModifierValue_Integer(const FName& metaModifierName)
{
	return GetMetamodifierValue<int32>(metaModifierName);
}

FVector UMetadataModifiers::GetMetaModifierValue_Vector(const FName& metaModifierName)
{
	return GetMetamodifierValue<FVector>(metaModifierName);
}

TArray<FName> UMetadataModifiers::GetMetaModifierNamesInUse() const
{
	TArray<FName> namesInUse;

	for (auto metaMod : MetaModifiers)
	{
		namesInUse.Add(metaMod.MetaModifierName);
	}

	return namesInUse;
}

bool UMetadataModifiers::IsMetamodifierNameInUse(const FName& metaModifierNameToFind) const
{
	ensure(!metaModifierNameToFind.IsNone());

	for (auto metaMod : MetaModifiers)
	{
		if (metaMod.MetaModifierName == metaModifierNameToFind)
		{
			return true;
		};
	}

	UE_LOG(LogMetaModifiers, Warning, TEXT("Metamodifier by the name of (%s) was not found on (%s)."), *metaModifierNameToFind.ToString(), *GetNameSafe(GetOwner()));

	return false;
}

void UMetadataModifiers::AddMetaModifier(const FMetaModifierProperty& metaMod)
{
	MetaModifiers.Add(metaMod);
}

template<class T> T
UMetadataModifiers::GetMetamodifierValue(const FName MetaModifierName) const
{
	//	Make sure that named metamod exists
	ensure(IsMetamodifierNameInUse(MetaModifierName));

	//	Get all the metamods with that name
	auto metaMods = GetMetaModifiersByName(MetaModifierName);
	//	This will be our local temp object of that type
	T null = T();
	//	This will be the compounded metamodifier value of all existing metamods of that name
	T compoundedValue = T();
	//	This is the C++ type name as string of that type
	const std::string type_str(typeid(null).name());

	//	Now go through all the metamods with that name
	for (auto& metaMod2 : metaMods)
	{
		//	Go through each property in the struct to look for a property that matches the type of the template type
		for (TFieldIterator<UProperty> struct_property(metaMod2.StaticStruct()); struct_property; ++struct_property)
		{
			const FString propertyTypeName = struct_property->GetCPPType();

			//	Find the last word in a string, that will always be our real type name
			const auto index = type_str.find_last_of(' ');
			const std::string last_word = type_str.substr(index + 1);
			const FString templateTypeName = FString(UTF8_TO_TCHAR(last_word.c_str()));

			if (propertyTypeName == templateTypeName)
			{
				const T& appendix = *(T*)struct_property->ContainerPtrToValuePtr<void>(&metaMod2);
				compoundedValue = compoundedValue + appendix;
			}
		}
	}

	//	Cast the return to the proper type
	return (T)(compoundedValue);
}

// Called when the game starts
void UMetadataModifiers::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void UMetadataModifiers::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
