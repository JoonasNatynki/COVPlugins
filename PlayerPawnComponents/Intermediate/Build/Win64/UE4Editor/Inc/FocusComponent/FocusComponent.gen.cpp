// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FocusComponent/Public/FocusComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFocusComponent() {}
// Cross Module References
	FOCUSCOMPONENT_API UFunction* Z_Construct_UDelegateFunction_FocusComponent_OnFocusedActorChanged__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_FocusComponent();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
	FOCUSCOMPONENT_API UClass* Z_Construct_UClass_UFocusComponent_NoRegister();
	FOCUSCOMPONENT_API UClass* Z_Construct_UClass_UFocusComponent();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	FOCUSCOMPONENT_API UFunction* Z_Construct_UFunction_UFocusComponent_GetCachedFocusedActor();
	FOCUSCOMPONENT_API UFunction* Z_Construct_UFunction_UFocusComponent_GetFocusedActor();
	FOCUSCOMPONENT_API UFunction* Z_Construct_UFunction_UFocusComponent_GetFocusWorldLocation();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	FOCUSCOMPONENT_API UFunction* Z_Construct_UFunction_UFocusComponent_SetFocusedActor();
	FOCUSCOMPONENT_API UFunction* Z_Construct_UFunction_UFocusComponent_UpdateFocusedActor();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_FocusComponent_OnFocusedActorChanged__DelegateSignature_Statics
	{
		struct _Script_FocusComponent_eventOnFocusedActorChanged_Parms
		{
			AActor* NewFocusedActor;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_NewFocusedActor;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UDelegateFunction_FocusComponent_OnFocusedActorChanged__DelegateSignature_Statics::NewProp_NewFocusedActor = { "NewFocusedActor", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_FocusComponent_eventOnFocusedActorChanged_Parms, NewFocusedActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FocusComponent_OnFocusedActorChanged__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FocusComponent_OnFocusedActorChanged__DelegateSignature_Statics::NewProp_NewFocusedActor,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_FocusComponent_OnFocusedActorChanged__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// Fill out your copyright notice in the Description page of Project Settings.\n" },
		{ "ModuleRelativePath", "Public/FocusComponent.h" },
		{ "ToolTip", "Fill out your copyright notice in the Description page of Project Settings." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FocusComponent_OnFocusedActorChanged__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FocusComponent, nullptr, "OnFocusedActorChanged__DelegateSignature", nullptr, nullptr, sizeof(_Script_FocusComponent_eventOnFocusedActorChanged_Parms), Z_Construct_UDelegateFunction_FocusComponent_OnFocusedActorChanged__DelegateSignature_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UDelegateFunction_FocusComponent_OnFocusedActorChanged__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_FocusComponent_OnFocusedActorChanged__DelegateSignature_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UDelegateFunction_FocusComponent_OnFocusedActorChanged__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_FocusComponent_OnFocusedActorChanged__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_FocusComponent_OnFocusedActorChanged__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	void UFocusComponent::StaticRegisterNativesUFocusComponent()
	{
		UClass* Class = UFocusComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetCachedFocusedActor", &UFocusComponent::execGetCachedFocusedActor },
			{ "GetFocusedActor", &UFocusComponent::execGetFocusedActor },
			{ "GetFocusWorldLocation", &UFocusComponent::execGetFocusWorldLocation },
			{ "SetFocusedActor", &UFocusComponent::execSetFocusedActor },
			{ "UpdateFocusedActor", &UFocusComponent::execUpdateFocusedActor },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UFocusComponent_GetCachedFocusedActor_Statics
	{
		struct FocusComponent_eventGetCachedFocusedActor_Parms
		{
			AActor* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFocusComponent_GetCachedFocusedActor_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FocusComponent_eventGetCachedFocusedActor_Parms, ReturnValue), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFocusComponent_GetCachedFocusedActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFocusComponent_GetCachedFocusedActor_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFocusComponent_GetCachedFocusedActor_Statics::Function_MetaDataParams[] = {
		{ "Category", "Focus" },
		{ "Comment", "//\x09Gets the cached focused actor from the last time the focus actor was updated.\n" },
		{ "ModuleRelativePath", "Public/FocusComponent.h" },
		{ "ToolTip", "Gets the cached focused actor from the last time the focus actor was updated." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFocusComponent_GetCachedFocusedActor_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFocusComponent, nullptr, "GetCachedFocusedActor", nullptr, nullptr, sizeof(FocusComponent_eventGetCachedFocusedActor_Parms), Z_Construct_UFunction_UFocusComponent_GetCachedFocusedActor_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_UFocusComponent_GetCachedFocusedActor_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFocusComponent_GetCachedFocusedActor_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_UFocusComponent_GetCachedFocusedActor_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFocusComponent_GetCachedFocusedActor()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFocusComponent_GetCachedFocusedActor_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFocusComponent_GetFocusedActor_Statics
	{
		struct FocusComponent_eventGetFocusedActor_Parms
		{
			AActor* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFocusComponent_GetFocusedActor_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FocusComponent_eventGetFocusedActor_Parms, ReturnValue), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFocusComponent_GetFocusedActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFocusComponent_GetFocusedActor_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFocusComponent_GetFocusedActor_Statics::Function_MetaDataParams[] = {
		{ "Category", "Focus" },
		{ "Comment", "//\x09Gets and updates the focused actor.\n" },
		{ "ModuleRelativePath", "Public/FocusComponent.h" },
		{ "ToolTip", "Gets and updates the focused actor." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFocusComponent_GetFocusedActor_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFocusComponent, nullptr, "GetFocusedActor", nullptr, nullptr, sizeof(FocusComponent_eventGetFocusedActor_Parms), Z_Construct_UFunction_UFocusComponent_GetFocusedActor_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_UFocusComponent_GetFocusedActor_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFocusComponent_GetFocusedActor_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_UFocusComponent_GetFocusedActor_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFocusComponent_GetFocusedActor()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFocusComponent_GetFocusedActor_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFocusComponent_GetFocusWorldLocation_Statics
	{
		struct FocusComponent_eventGetFocusWorldLocation_Parms
		{
			FVector ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFocusComponent_GetFocusWorldLocation_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FocusComponent_eventGetFocusWorldLocation_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFocusComponent_GetFocusWorldLocation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFocusComponent_GetFocusWorldLocation_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFocusComponent_GetFocusWorldLocation_Statics::Function_MetaDataParams[] = {
		{ "Category", "Focus" },
		{ "ModuleRelativePath", "Public/FocusComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFocusComponent_GetFocusWorldLocation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFocusComponent, nullptr, "GetFocusWorldLocation", nullptr, nullptr, sizeof(FocusComponent_eventGetFocusWorldLocation_Parms), Z_Construct_UFunction_UFocusComponent_GetFocusWorldLocation_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_UFocusComponent_GetFocusWorldLocation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFocusComponent_GetFocusWorldLocation_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_UFocusComponent_GetFocusWorldLocation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFocusComponent_GetFocusWorldLocation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFocusComponent_GetFocusWorldLocation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFocusComponent_SetFocusedActor_Statics
	{
		struct FocusComponent_eventSetFocusedActor_Parms
		{
			AActor* newFocus;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_newFocus;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFocusComponent_SetFocusedActor_Statics::NewProp_newFocus = { "newFocus", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FocusComponent_eventSetFocusedActor_Parms, newFocus), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFocusComponent_SetFocusedActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFocusComponent_SetFocusedActor_Statics::NewProp_newFocus,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFocusComponent_SetFocusedActor_Statics::Function_MetaDataParams[] = {
		{ "Category", "Focus" },
		{ "ModuleRelativePath", "Public/FocusComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFocusComponent_SetFocusedActor_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFocusComponent, nullptr, "SetFocusedActor", nullptr, nullptr, sizeof(FocusComponent_eventSetFocusedActor_Parms), Z_Construct_UFunction_UFocusComponent_SetFocusedActor_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_UFocusComponent_SetFocusedActor_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFocusComponent_SetFocusedActor_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_UFocusComponent_SetFocusedActor_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFocusComponent_SetFocusedActor()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFocusComponent_SetFocusedActor_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFocusComponent_UpdateFocusedActor_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFocusComponent_UpdateFocusedActor_Statics::Function_MetaDataParams[] = {
		{ "Category", "Focus" },
		{ "Comment", "//\x09Goes through the logic of how the focus actor is determined and updates the cached focused actor variable.\n" },
		{ "ModuleRelativePath", "Public/FocusComponent.h" },
		{ "ToolTip", "Goes through the logic of how the focus actor is determined and updates the cached focused actor variable." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFocusComponent_UpdateFocusedActor_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFocusComponent, nullptr, "UpdateFocusedActor", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFocusComponent_UpdateFocusedActor_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_UFocusComponent_UpdateFocusedActor_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFocusComponent_UpdateFocusedActor()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFocusComponent_UpdateFocusedActor_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UFocusComponent_NoRegister()
	{
		return UFocusComponent::StaticClass();
	}
	struct Z_Construct_UClass_UFocusComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bShowDebug_MetaData[];
#endif
		static void NewProp_bShowDebug_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bShowDebug;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bFocusOnlyOnFocusables_MetaData[];
#endif
		static void NewProp_bFocusOnlyOnFocusables_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bFocusOnlyOnFocusables;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FocusingRadiusExtent_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_FocusingRadiusExtent;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bDeveloperMode_MetaData[];
#endif
		static void NewProp_bDeveloperMode_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bDeveloperMode;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FocusingMaxDistance_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_FocusingMaxDistance;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FocusWorldLocation_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_FocusWorldLocation;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CachedFocusedActor_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CachedFocusedActor;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnFocusedActorChanged_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnFocusedActorChanged;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFocusComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_FocusComponent,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UFocusComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UFocusComponent_GetCachedFocusedActor, "GetCachedFocusedActor" }, // 4066728932
		{ &Z_Construct_UFunction_UFocusComponent_GetFocusedActor, "GetFocusedActor" }, // 3192182318
		{ &Z_Construct_UFunction_UFocusComponent_GetFocusWorldLocation, "GetFocusWorldLocation" }, // 446574063
		{ &Z_Construct_UFunction_UFocusComponent_SetFocusedActor, "SetFocusedActor" }, // 3068692976
		{ &Z_Construct_UFunction_UFocusComponent_UpdateFocusedActor, "UpdateFocusedActor" }, // 1464377451
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFocusComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Custom" },
		{ "Comment", "//\x09""Component that casts either a ray from the camera or a more complex area focus mechanic to determine which object in the game world is being focused on.\n" },
		{ "IncludePath", "FocusComponent.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/FocusComponent.h" },
		{ "ShortTooltip", "Component used for focusing on objects." },
		{ "ToolTip", "Component that casts either a ray from the camera or a more complex area focus mechanic to determine which object in the game world is being focused on." },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFocusComponent_Statics::NewProp_bShowDebug_MetaData[] = {
		{ "Category", "Debug" },
		{ "ModuleRelativePath", "Public/FocusComponent.h" },
	};
#endif
	void Z_Construct_UClass_UFocusComponent_Statics::NewProp_bShowDebug_SetBit(void* Obj)
	{
		((UFocusComponent*)Obj)->bShowDebug = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UFocusComponent_Statics::NewProp_bShowDebug = { "bShowDebug", nullptr, (EPropertyFlags)0x0010000000010005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UFocusComponent), &Z_Construct_UClass_UFocusComponent_Statics::NewProp_bShowDebug_SetBit, METADATA_PARAMS(Z_Construct_UClass_UFocusComponent_Statics::NewProp_bShowDebug_MetaData, ARRAY_COUNT(Z_Construct_UClass_UFocusComponent_Statics::NewProp_bShowDebug_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFocusComponent_Statics::NewProp_bFocusOnlyOnFocusables_MetaData[] = {
		{ "Category", "Debug" },
		{ "Comment", "//\x09Whether to ignore all other actors but the ones with the FocusableComponent\n" },
		{ "ModuleRelativePath", "Public/FocusComponent.h" },
		{ "ToolTip", "Whether to ignore all other actors but the ones with the FocusableComponent" },
	};
#endif
	void Z_Construct_UClass_UFocusComponent_Statics::NewProp_bFocusOnlyOnFocusables_SetBit(void* Obj)
	{
		((UFocusComponent*)Obj)->bFocusOnlyOnFocusables = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UFocusComponent_Statics::NewProp_bFocusOnlyOnFocusables = { "bFocusOnlyOnFocusables", nullptr, (EPropertyFlags)0x0010000000010005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UFocusComponent), &Z_Construct_UClass_UFocusComponent_Statics::NewProp_bFocusOnlyOnFocusables_SetBit, METADATA_PARAMS(Z_Construct_UClass_UFocusComponent_Statics::NewProp_bFocusOnlyOnFocusables_MetaData, ARRAY_COUNT(Z_Construct_UClass_UFocusComponent_Statics::NewProp_bFocusOnlyOnFocusables_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFocusComponent_Statics::NewProp_FocusingRadiusExtent_MetaData[] = {
		{ "Category", "Focus" },
		{ "Comment", "//\x09How far away from the focusing center line can actors be focused at. Used in focusing on objects that are not directly being focused at\n" },
		{ "ModuleRelativePath", "Public/FocusComponent.h" },
		{ "ToolTip", "How far away from the focusing center line can actors be focused at. Used in focusing on objects that are not directly being focused at" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UFocusComponent_Statics::NewProp_FocusingRadiusExtent = { "FocusingRadiusExtent", nullptr, (EPropertyFlags)0x0010000000010005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFocusComponent, FocusingRadiusExtent), METADATA_PARAMS(Z_Construct_UClass_UFocusComponent_Statics::NewProp_FocusingRadiusExtent_MetaData, ARRAY_COUNT(Z_Construct_UClass_UFocusComponent_Statics::NewProp_FocusingRadiusExtent_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFocusComponent_Statics::NewProp_bDeveloperMode_MetaData[] = {
		{ "Category", "Focus" },
		{ "Comment", "//\x09If TRUE, you can focus on everything and on focusable things regardless of their set distance limits.\n" },
		{ "ModuleRelativePath", "Public/FocusComponent.h" },
		{ "ToolTip", "If TRUE, you can focus on everything and on focusable things regardless of their set distance limits." },
	};
#endif
	void Z_Construct_UClass_UFocusComponent_Statics::NewProp_bDeveloperMode_SetBit(void* Obj)
	{
		((UFocusComponent*)Obj)->bDeveloperMode = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UFocusComponent_Statics::NewProp_bDeveloperMode = { "bDeveloperMode", nullptr, (EPropertyFlags)0x0010000000010005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UFocusComponent), &Z_Construct_UClass_UFocusComponent_Statics::NewProp_bDeveloperMode_SetBit, METADATA_PARAMS(Z_Construct_UClass_UFocusComponent_Statics::NewProp_bDeveloperMode_MetaData, ARRAY_COUNT(Z_Construct_UClass_UFocusComponent_Statics::NewProp_bDeveloperMode_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFocusComponent_Statics::NewProp_FocusingMaxDistance_MetaData[] = {
		{ "Category", "Focus" },
		{ "ModuleRelativePath", "Public/FocusComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UFocusComponent_Statics::NewProp_FocusingMaxDistance = { "FocusingMaxDistance", nullptr, (EPropertyFlags)0x0010000000010005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFocusComponent, FocusingMaxDistance), METADATA_PARAMS(Z_Construct_UClass_UFocusComponent_Statics::NewProp_FocusingMaxDistance_MetaData, ARRAY_COUNT(Z_Construct_UClass_UFocusComponent_Statics::NewProp_FocusingMaxDistance_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFocusComponent_Statics::NewProp_FocusWorldLocation_MetaData[] = {
		{ "Category", "Focus" },
		{ "ModuleRelativePath", "Public/FocusComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFocusComponent_Statics::NewProp_FocusWorldLocation = { "FocusWorldLocation", nullptr, (EPropertyFlags)0x0010000000022015, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFocusComponent, FocusWorldLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UClass_UFocusComponent_Statics::NewProp_FocusWorldLocation_MetaData, ARRAY_COUNT(Z_Construct_UClass_UFocusComponent_Statics::NewProp_FocusWorldLocation_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFocusComponent_Statics::NewProp_CachedFocusedActor_MetaData[] = {
		{ "Category", "Focus" },
		{ "ModuleRelativePath", "Public/FocusComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UFocusComponent_Statics::NewProp_CachedFocusedActor = { "CachedFocusedActor", nullptr, (EPropertyFlags)0x0010000000022015, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFocusComponent, CachedFocusedActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UFocusComponent_Statics::NewProp_CachedFocusedActor_MetaData, ARRAY_COUNT(Z_Construct_UClass_UFocusComponent_Statics::NewProp_CachedFocusedActor_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFocusComponent_Statics::NewProp_OnFocusedActorChanged_MetaData[] = {
		{ "ModuleRelativePath", "Public/FocusComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UFocusComponent_Statics::NewProp_OnFocusedActorChanged = { "OnFocusedActorChanged", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFocusComponent, OnFocusedActorChanged), Z_Construct_UDelegateFunction_FocusComponent_OnFocusedActorChanged__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UFocusComponent_Statics::NewProp_OnFocusedActorChanged_MetaData, ARRAY_COUNT(Z_Construct_UClass_UFocusComponent_Statics::NewProp_OnFocusedActorChanged_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UFocusComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFocusComponent_Statics::NewProp_bShowDebug,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFocusComponent_Statics::NewProp_bFocusOnlyOnFocusables,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFocusComponent_Statics::NewProp_FocusingRadiusExtent,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFocusComponent_Statics::NewProp_bDeveloperMode,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFocusComponent_Statics::NewProp_FocusingMaxDistance,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFocusComponent_Statics::NewProp_FocusWorldLocation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFocusComponent_Statics::NewProp_CachedFocusedActor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFocusComponent_Statics::NewProp_OnFocusedActorChanged,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFocusComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFocusComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFocusComponent_Statics::ClassParams = {
		&UFocusComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UFocusComponent_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		ARRAY_COUNT(FuncInfo),
		ARRAY_COUNT(Z_Construct_UClass_UFocusComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UFocusComponent_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_UFocusComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFocusComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UFocusComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UFocusComponent, 927396467);
	template<> FOCUSCOMPONENT_API UClass* StaticClass<UFocusComponent>()
	{
		return UFocusComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UFocusComponent(Z_Construct_UClass_UFocusComponent, &UFocusComponent::StaticClass, TEXT("/Script/FocusComponent"), TEXT("UFocusComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFocusComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
