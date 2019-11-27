// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef FOCUSCOMPONENT_FocusableComponent_generated_h
#error "FocusableComponent.generated.h already included, missing '#pragma once' in FocusableComponent.h"
#endif
#define FOCUSCOMPONENT_FocusableComponent_generated_h

#define COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusableComponent_h_14_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execSetIsFocusable) \
	{ \
		P_GET_UBOOL(Z_Param_bIsFocusable); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetIsFocusable(Z_Param_bIsFocusable); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetFocusDistance) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(float*)Z_Param__Result=P_THIS->GetFocusDistance(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execIsFocusable) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->IsFocusable(); \
		P_NATIVE_END; \
	}


#define COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusableComponent_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSetIsFocusable) \
	{ \
		P_GET_UBOOL(Z_Param_bIsFocusable); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetIsFocusable(Z_Param_bIsFocusable); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetFocusDistance) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(float*)Z_Param__Result=P_THIS->GetFocusDistance(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execIsFocusable) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->IsFocusable(); \
		P_NATIVE_END; \
	}


#define COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusableComponent_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUFocusableComponent(); \
	friend struct Z_Construct_UClass_UFocusableComponent_Statics; \
public: \
	DECLARE_CLASS(UFocusableComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FocusComponent"), NO_API) \
	DECLARE_SERIALIZER(UFocusableComponent)


#define COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusableComponent_h_14_INCLASS \
private: \
	static void StaticRegisterNativesUFocusableComponent(); \
	friend struct Z_Construct_UClass_UFocusableComponent_Statics; \
public: \
	DECLARE_CLASS(UFocusableComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FocusComponent"), NO_API) \
	DECLARE_SERIALIZER(UFocusableComponent)


#define COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusableComponent_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UFocusableComponent(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UFocusableComponent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UFocusableComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UFocusableComponent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UFocusableComponent(UFocusableComponent&&); \
	NO_API UFocusableComponent(const UFocusableComponent&); \
public:


#define COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusableComponent_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UFocusableComponent(UFocusableComponent&&); \
	NO_API UFocusableComponent(const UFocusableComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UFocusableComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UFocusableComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UFocusableComponent)


#define COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusableComponent_h_14_PRIVATE_PROPERTY_OFFSET
#define COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusableComponent_h_11_PROLOG
#define COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusableComponent_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusableComponent_h_14_PRIVATE_PROPERTY_OFFSET \
	COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusableComponent_h_14_RPC_WRAPPERS \
	COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusableComponent_h_14_INCLASS \
	COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusableComponent_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusableComponent_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusableComponent_h_14_PRIVATE_PROPERTY_OFFSET \
	COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusableComponent_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusableComponent_h_14_INCLASS_NO_PURE_DECLS \
	COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusableComponent_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FOCUSCOMPONENT_API UClass* StaticClass<class UFocusableComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusableComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
