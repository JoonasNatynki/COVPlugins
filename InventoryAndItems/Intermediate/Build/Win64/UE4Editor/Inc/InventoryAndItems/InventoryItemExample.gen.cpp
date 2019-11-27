// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "InventoryAndItems/Public/InventoryItemExample.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeInventoryItemExample() {}
// Cross Module References
	INVENTORYANDITEMS_API UClass* Z_Construct_UClass_AInventoryItemExample_NoRegister();
	INVENTORYANDITEMS_API UClass* Z_Construct_UClass_AInventoryItemExample();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_InventoryAndItems();
	INVENTORYANDITEMS_API UClass* Z_Construct_UClass_UInventoryItemComponent_NoRegister();
// End Cross Module References
	void AInventoryItemExample::StaticRegisterNativesAInventoryItemExample()
	{
	}
	UClass* Z_Construct_UClass_AInventoryItemExample_NoRegister()
	{
		return AInventoryItemExample::StaticClass();
	}
	struct Z_Construct_UClass_AInventoryItemExample_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Damage_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Damage;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Ammo_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Ammo;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InventoryItem_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_InventoryItem;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AInventoryItemExample_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_InventoryAndItems,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AInventoryItemExample_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "InventoryItemExample.h" },
		{ "ModuleRelativePath", "Public/InventoryItemExample.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AInventoryItemExample_Statics::NewProp_Damage_MetaData[] = {
		{ "Category", "Gun" },
		{ "Comment", "//\x09Will carry over to the other actor version\n//\x09This is an example of a property that will automatically be passed on between collectible/inventory version(s) of the same item\n" },
		{ "INVENTORYPROPERTY", "" },
		{ "ModuleRelativePath", "Public/InventoryItemExample.h" },
		{ "ToolTip", "Will carry over to the other actor version\nThis is an example of a property that will automatically be passed on between collectible/inventory version(s) of the same item" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AInventoryItemExample_Statics::NewProp_Damage = { "Damage", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AInventoryItemExample, Damage), METADATA_PARAMS(Z_Construct_UClass_AInventoryItemExample_Statics::NewProp_Damage_MetaData, ARRAY_COUNT(Z_Construct_UClass_AInventoryItemExample_Statics::NewProp_Damage_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AInventoryItemExample_Statics::NewProp_Ammo_MetaData[] = {
		{ "Category", "Gun" },
		{ "Comment", "//\x09This is an example of a property that will automatically be passed on between collectible/inventory version(s) of the same item\n" },
		{ "INVENTORYPROPERTY", "" },
		{ "ModuleRelativePath", "Public/InventoryItemExample.h" },
		{ "ToolTip", "This is an example of a property that will automatically be passed on between collectible/inventory version(s) of the same item" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_AInventoryItemExample_Statics::NewProp_Ammo = { "Ammo", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AInventoryItemExample, Ammo), METADATA_PARAMS(Z_Construct_UClass_AInventoryItemExample_Statics::NewProp_Ammo_MetaData, ARRAY_COUNT(Z_Construct_UClass_AInventoryItemExample_Statics::NewProp_Ammo_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AInventoryItemExample_Statics::NewProp_InventoryItem_MetaData[] = {
		{ "Category", "Collectible" },
		{ "Comment", "//\x09""All actors that can be put into an inventory will need to have the inventory item component\n" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/InventoryItemExample.h" },
		{ "ToolTip", "All actors that can be put into an inventory will need to have the inventory item component" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AInventoryItemExample_Statics::NewProp_InventoryItem = { "InventoryItem", nullptr, (EPropertyFlags)0x00100000000b001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AInventoryItemExample, InventoryItem), Z_Construct_UClass_UInventoryItemComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AInventoryItemExample_Statics::NewProp_InventoryItem_MetaData, ARRAY_COUNT(Z_Construct_UClass_AInventoryItemExample_Statics::NewProp_InventoryItem_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AInventoryItemExample_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInventoryItemExample_Statics::NewProp_Damage,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInventoryItemExample_Statics::NewProp_Ammo,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AInventoryItemExample_Statics::NewProp_InventoryItem,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AInventoryItemExample_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AInventoryItemExample>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AInventoryItemExample_Statics::ClassParams = {
		&AInventoryItemExample::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AInventoryItemExample_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		ARRAY_COUNT(Z_Construct_UClass_AInventoryItemExample_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_AInventoryItemExample_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AInventoryItemExample_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AInventoryItemExample()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AInventoryItemExample_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AInventoryItemExample, 1981253455);
	template<> INVENTORYANDITEMS_API UClass* StaticClass<AInventoryItemExample>()
	{
		return AInventoryItemExample::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AInventoryItemExample(Z_Construct_UClass_AInventoryItemExample, &AInventoryItemExample::StaticClass, TEXT("/Script/InventoryAndItems"), TEXT("AInventoryItemExample"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AInventoryItemExample);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
