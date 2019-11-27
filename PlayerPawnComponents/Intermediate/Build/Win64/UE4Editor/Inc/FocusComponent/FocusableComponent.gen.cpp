// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FocusComponent/Public/FocusableComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFocusableComponent() {}
// Cross Module References
	FOCUSCOMPONENT_API UClass* Z_Construct_UClass_UFocusableComponent_NoRegister();
	FOCUSCOMPONENT_API UClass* Z_Construct_UClass_UFocusableComponent();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	UPackage* Z_Construct_UPackage__Script_FocusComponent();
	FOCUSCOMPONENT_API UFunction* Z_Construct_UFunction_UFocusableComponent_GetFocusDistance();
	FOCUSCOMPONENT_API UFunction* Z_Construct_UFunction_UFocusableComponent_IsFocusable();
	FOCUSCOMPONENT_API UFunction* Z_Construct_UFunction_UFocusableComponent_SetIsFocusable();
// End Cross Module References
	void UFocusableComponent::StaticRegisterNativesUFocusableComponent()
	{
		UClass* Class = UFocusableComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetFocusDistance", &UFocusableComponent::execGetFocusDistance },
			{ "IsFocusable", &UFocusableComponent::execIsFocusable },
			{ "SetIsFocusable", &UFocusableComponent::execSetIsFocusable },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UFocusableComponent_GetFocusDistance_Statics
	{
		struct FocusableComponent_eventGetFocusDistance_Parms
		{
			float ReturnValue;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFocusableComponent_GetFocusDistance_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FocusableComponent_eventGetFocusDistance_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFocusableComponent_GetFocusDistance_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFocusableComponent_GetFocusDistance_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFocusableComponent_GetFocusDistance_Statics::Function_MetaDataParams[] = {
		{ "Category", "Focusable" },
		{ "ModuleRelativePath", "Public/FocusableComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFocusableComponent_GetFocusDistance_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFocusableComponent, nullptr, "GetFocusDistance", nullptr, nullptr, sizeof(FocusableComponent_eventGetFocusDistance_Parms), Z_Construct_UFunction_UFocusableComponent_GetFocusDistance_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_UFocusableComponent_GetFocusDistance_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFocusableComponent_GetFocusDistance_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_UFocusableComponent_GetFocusDistance_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFocusableComponent_GetFocusDistance()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFocusableComponent_GetFocusDistance_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFocusableComponent_IsFocusable_Statics
	{
		struct FocusableComponent_eventIsFocusable_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UFocusableComponent_IsFocusable_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((FocusableComponent_eventIsFocusable_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFocusableComponent_IsFocusable_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FocusableComponent_eventIsFocusable_Parms), &Z_Construct_UFunction_UFocusableComponent_IsFocusable_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFocusableComponent_IsFocusable_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFocusableComponent_IsFocusable_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFocusableComponent_IsFocusable_Statics::Function_MetaDataParams[] = {
		{ "Category", "Focusable" },
		{ "ModuleRelativePath", "Public/FocusableComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFocusableComponent_IsFocusable_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFocusableComponent, nullptr, "IsFocusable", nullptr, nullptr, sizeof(FocusableComponent_eventIsFocusable_Parms), Z_Construct_UFunction_UFocusableComponent_IsFocusable_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_UFocusableComponent_IsFocusable_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFocusableComponent_IsFocusable_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_UFocusableComponent_IsFocusable_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFocusableComponent_IsFocusable()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFocusableComponent_IsFocusable_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFocusableComponent_SetIsFocusable_Statics
	{
		struct FocusableComponent_eventSetIsFocusable_Parms
		{
			bool bIsFocusable;
		};
		static void NewProp_bIsFocusable_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bIsFocusable;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UFocusableComponent_SetIsFocusable_Statics::NewProp_bIsFocusable_SetBit(void* Obj)
	{
		((FocusableComponent_eventSetIsFocusable_Parms*)Obj)->bIsFocusable = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFocusableComponent_SetIsFocusable_Statics::NewProp_bIsFocusable = { "bIsFocusable", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FocusableComponent_eventSetIsFocusable_Parms), &Z_Construct_UFunction_UFocusableComponent_SetIsFocusable_Statics::NewProp_bIsFocusable_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFocusableComponent_SetIsFocusable_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFocusableComponent_SetIsFocusable_Statics::NewProp_bIsFocusable,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFocusableComponent_SetIsFocusable_Statics::Function_MetaDataParams[] = {
		{ "Category", "Focusable" },
		{ "ModuleRelativePath", "Public/FocusableComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFocusableComponent_SetIsFocusable_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFocusableComponent, nullptr, "SetIsFocusable", nullptr, nullptr, sizeof(FocusableComponent_eventSetIsFocusable_Parms), Z_Construct_UFunction_UFocusableComponent_SetIsFocusable_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_UFocusableComponent_SetIsFocusable_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFocusableComponent_SetIsFocusable_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_UFocusableComponent_SetIsFocusable_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFocusableComponent_SetIsFocusable()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFocusableComponent_SetIsFocusable_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UFocusableComponent_NoRegister()
	{
		return UFocusableComponent::StaticClass();
	}
	struct Z_Construct_UClass_UFocusableComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FocusDistance_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_FocusDistance;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bCanBeFocusedAt_MetaData[];
#endif
		static void NewProp_bCanBeFocusedAt_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bCanBeFocusedAt;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFocusableComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_FocusComponent,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UFocusableComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UFocusableComponent_GetFocusDistance, "GetFocusDistance" }, // 643855111
		{ &Z_Construct_UFunction_UFocusableComponent_IsFocusable, "IsFocusable" }, // 1811560143
		{ &Z_Construct_UFunction_UFocusableComponent_SetIsFocusable, "SetIsFocusable" }, // 771981561
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFocusableComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "FocusableComponent.h" },
		{ "ModuleRelativePath", "Public/FocusableComponent.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFocusableComponent_Statics::NewProp_FocusDistance_MetaData[] = {
		{ "Category", "Focusable" },
		{ "Comment", "//\x09The maximum distance this focusable can be focused at maximum\n" },
		{ "ModuleRelativePath", "Public/FocusableComponent.h" },
		{ "ToolTip", "The maximum distance this focusable can be focused at maximum" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UFocusableComponent_Statics::NewProp_FocusDistance = { "FocusDistance", nullptr, (EPropertyFlags)0x0010000000010001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFocusableComponent, FocusDistance), METADATA_PARAMS(Z_Construct_UClass_UFocusableComponent_Statics::NewProp_FocusDistance_MetaData, ARRAY_COUNT(Z_Construct_UClass_UFocusableComponent_Statics::NewProp_FocusDistance_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFocusableComponent_Statics::NewProp_bCanBeFocusedAt_MetaData[] = {
		{ "Category", "Focusable" },
		{ "ModuleRelativePath", "Public/FocusableComponent.h" },
	};
#endif
	void Z_Construct_UClass_UFocusableComponent_Statics::NewProp_bCanBeFocusedAt_SetBit(void* Obj)
	{
		((UFocusableComponent*)Obj)->bCanBeFocusedAt = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UFocusableComponent_Statics::NewProp_bCanBeFocusedAt = { "bCanBeFocusedAt", nullptr, (EPropertyFlags)0x0010000000010021, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UFocusableComponent), &Z_Construct_UClass_UFocusableComponent_Statics::NewProp_bCanBeFocusedAt_SetBit, METADATA_PARAMS(Z_Construct_UClass_UFocusableComponent_Statics::NewProp_bCanBeFocusedAt_MetaData, ARRAY_COUNT(Z_Construct_UClass_UFocusableComponent_Statics::NewProp_bCanBeFocusedAt_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UFocusableComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFocusableComponent_Statics::NewProp_FocusDistance,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFocusableComponent_Statics::NewProp_bCanBeFocusedAt,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFocusableComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFocusableComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFocusableComponent_Statics::ClassParams = {
		&UFocusableComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UFocusableComponent_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		ARRAY_COUNT(FuncInfo),
		ARRAY_COUNT(Z_Construct_UClass_UFocusableComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UFocusableComponent_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_UFocusableComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFocusableComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UFocusableComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UFocusableComponent, 3018520795);
	template<> FOCUSCOMPONENT_API UClass* StaticClass<UFocusableComponent>()
	{
		return UFocusableComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UFocusableComponent(Z_Construct_UClass_UFocusableComponent, &UFocusableComponent::StaticClass, TEXT("/Script/FocusComponent"), TEXT("UFocusableComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFocusableComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
