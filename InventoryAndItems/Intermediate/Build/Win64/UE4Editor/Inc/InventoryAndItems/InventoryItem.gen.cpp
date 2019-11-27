// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "InventoryAndItems/Public/InventoryItem.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeInventoryItem() {}
// Cross Module References
	INVENTORYANDITEMS_API UClass* Z_Construct_UClass_UInventoryItemComponent_NoRegister();
	INVENTORYANDITEMS_API UClass* Z_Construct_UClass_UInventoryItemComponent();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	UPackage* Z_Construct_UPackage__Script_InventoryAndItems();
	INVENTORYANDITEMS_API UFunction* Z_Construct_UFunction_UInventoryItemComponent_GetItemGUID();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid();
	INVENTORYANDITEMS_API UFunction* Z_Construct_UFunction_UInventoryItemComponent_OnRep_ItemGUID();
	INVENTORYANDITEMS_API UFunction* Z_Construct_UFunction_UInventoryItemComponent_SetItemGUID();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
// End Cross Module References
	void UInventoryItemComponent::StaticRegisterNativesUInventoryItemComponent()
	{
		UClass* Class = UInventoryItemComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetItemGUID", &UInventoryItemComponent::execGetItemGUID },
			{ "OnRep_ItemGUID", &UInventoryItemComponent::execOnRep_ItemGUID },
			{ "SetItemGUID", &UInventoryItemComponent::execSetItemGUID },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UInventoryItemComponent_GetItemGUID_Statics
	{
		struct InventoryItemComponent_eventGetItemGUID_Parms
		{
			FGuid ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UInventoryItemComponent_GetItemGUID_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(InventoryItemComponent_eventGetItemGUID_Parms, ReturnValue), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UInventoryItemComponent_GetItemGUID_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInventoryItemComponent_GetItemGUID_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UInventoryItemComponent_GetItemGUID_Statics::Function_MetaDataParams[] = {
		{ "Category", "InventoryItem" },
		{ "ModuleRelativePath", "Public/InventoryItem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UInventoryItemComponent_GetItemGUID_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UInventoryItemComponent, nullptr, "GetItemGUID", nullptr, nullptr, sizeof(InventoryItemComponent_eventGetItemGUID_Parms), Z_Construct_UFunction_UInventoryItemComponent_GetItemGUID_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_UInventoryItemComponent_GetItemGUID_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UInventoryItemComponent_GetItemGUID_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_UInventoryItemComponent_GetItemGUID_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UInventoryItemComponent_GetItemGUID()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UInventoryItemComponent_GetItemGUID_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UInventoryItemComponent_OnRep_ItemGUID_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UInventoryItemComponent_OnRep_ItemGUID_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/InventoryItem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UInventoryItemComponent_OnRep_ItemGUID_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UInventoryItemComponent, nullptr, "OnRep_ItemGUID", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UInventoryItemComponent_OnRep_ItemGUID_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_UInventoryItemComponent_OnRep_ItemGUID_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UInventoryItemComponent_OnRep_ItemGUID()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UInventoryItemComponent_OnRep_ItemGUID_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UInventoryItemComponent_SetItemGUID_Statics
	{
		struct InventoryItemComponent_eventSetItemGUID_Parms
		{
			FGuid itemGuid;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_itemGuid;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UInventoryItemComponent_SetItemGUID_Statics::NewProp_itemGuid = { "itemGuid", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(InventoryItemComponent_eventSetItemGUID_Parms, itemGuid), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UInventoryItemComponent_SetItemGUID_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UInventoryItemComponent_SetItemGUID_Statics::NewProp_itemGuid,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UInventoryItemComponent_SetItemGUID_Statics::Function_MetaDataParams[] = {
		{ "Category", "InventoryItem" },
		{ "ModuleRelativePath", "Public/InventoryItem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UInventoryItemComponent_SetItemGUID_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UInventoryItemComponent, nullptr, "SetItemGUID", nullptr, nullptr, sizeof(InventoryItemComponent_eventSetItemGUID_Parms), Z_Construct_UFunction_UInventoryItemComponent_SetItemGUID_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_UInventoryItemComponent_SetItemGUID_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820405, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UInventoryItemComponent_SetItemGUID_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_UInventoryItemComponent_SetItemGUID_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UInventoryItemComponent_SetItemGUID()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UInventoryItemComponent_SetItemGUID_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UInventoryItemComponent_NoRegister()
	{
		return UInventoryItemComponent::StaticClass();
	}
	struct Z_Construct_UClass_UInventoryItemComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ItemGUID_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ItemGUID;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CorrespondingActorClassToSpawn_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_CorrespondingActorClassToSpawn;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UInventoryItemComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_InventoryAndItems,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UInventoryItemComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UInventoryItemComponent_GetItemGUID, "GetItemGUID" }, // 1085618773
		{ &Z_Construct_UFunction_UInventoryItemComponent_OnRep_ItemGUID, "OnRep_ItemGUID" }, // 1944047830
		{ &Z_Construct_UFunction_UInventoryItemComponent_SetItemGUID, "SetItemGUID" }, // 738280850
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UInventoryItemComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "InventoryItem.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/InventoryItem.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UInventoryItemComponent_Statics::NewProp_ItemGUID_MetaData[] = {
		{ "Category", "InventoryItem" },
		{ "ModuleRelativePath", "Public/InventoryItem.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UInventoryItemComponent_Statics::NewProp_ItemGUID = { "ItemGUID", "OnRep_ItemGUID", (EPropertyFlags)0x0010000100020021, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UInventoryItemComponent, ItemGUID), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(Z_Construct_UClass_UInventoryItemComponent_Statics::NewProp_ItemGUID_MetaData, ARRAY_COUNT(Z_Construct_UClass_UInventoryItemComponent_Statics::NewProp_ItemGUID_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UInventoryItemComponent_Statics::NewProp_CorrespondingActorClassToSpawn_MetaData[] = {
		{ "Category", "InventoryItem" },
		{ "ModuleRelativePath", "Public/InventoryItem.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_UInventoryItemComponent_Statics::NewProp_CorrespondingActorClassToSpawn = { "CorrespondingActorClassToSpawn", nullptr, (EPropertyFlags)0x0014000000010001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UInventoryItemComponent, CorrespondingActorClassToSpawn), Z_Construct_UClass_AActor_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_UInventoryItemComponent_Statics::NewProp_CorrespondingActorClassToSpawn_MetaData, ARRAY_COUNT(Z_Construct_UClass_UInventoryItemComponent_Statics::NewProp_CorrespondingActorClassToSpawn_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UInventoryItemComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInventoryItemComponent_Statics::NewProp_ItemGUID,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UInventoryItemComponent_Statics::NewProp_CorrespondingActorClassToSpawn,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UInventoryItemComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UInventoryItemComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UInventoryItemComponent_Statics::ClassParams = {
		&UInventoryItemComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UInventoryItemComponent_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		ARRAY_COUNT(FuncInfo),
		ARRAY_COUNT(Z_Construct_UClass_UInventoryItemComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UInventoryItemComponent_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_UInventoryItemComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UInventoryItemComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UInventoryItemComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UInventoryItemComponent, 1495395012);
	template<> INVENTORYANDITEMS_API UClass* StaticClass<UInventoryItemComponent>()
	{
		return UInventoryItemComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UInventoryItemComponent(Z_Construct_UClass_UInventoryItemComponent, &UInventoryItemComponent::StaticClass, TEXT("/Script/InventoryAndItems"), TEXT("UInventoryItemComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UInventoryItemComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
