// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
struct FVector;
#ifdef FOCUSCOMPONENT_FocusComponent_generated_h
#error "FocusComponent.generated.h already included, missing '#pragma once' in FocusComponent.h"
#endif
#define FOCUSCOMPONENT_FocusComponent_generated_h

#define COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusComponent_h_27_DELEGATE \
struct _Script_FocusComponent_eventOnFocusedActorChanged_Parms \
{ \
	AActor* NewFocusedActor; \
}; \
static inline void FOnFocusedActorChanged_DelegateWrapper(const FMulticastScriptDelegate& OnFocusedActorChanged, AActor* NewFocusedActor) \
{ \
	_Script_FocusComponent_eventOnFocusedActorChanged_Parms Parms; \
	Parms.NewFocusedActor=NewFocusedActor; \
	OnFocusedActorChanged.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusComponent_h_35_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execSetFocusedActor) \
	{ \
		P_GET_OBJECT(AActor,Z_Param_newFocus); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetFocusedActor(Z_Param_newFocus); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execUpdateFocusedActor) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->UpdateFocusedActor(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetFocusWorldLocation) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FVector*)Z_Param__Result=P_THIS->GetFocusWorldLocation(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetCachedFocusedActor) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(AActor**)Z_Param__Result=P_THIS->GetCachedFocusedActor(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetFocusedActor) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(AActor**)Z_Param__Result=P_THIS->GetFocusedActor(); \
		P_NATIVE_END; \
	}


#define COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusComponent_h_35_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSetFocusedActor) \
	{ \
		P_GET_OBJECT(AActor,Z_Param_newFocus); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetFocusedActor(Z_Param_newFocus); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execUpdateFocusedActor) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->UpdateFocusedActor(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetFocusWorldLocation) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FVector*)Z_Param__Result=P_THIS->GetFocusWorldLocation(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetCachedFocusedActor) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(AActor**)Z_Param__Result=P_THIS->GetCachedFocusedActor(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetFocusedActor) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(AActor**)Z_Param__Result=P_THIS->GetFocusedActor(); \
		P_NATIVE_END; \
	}


#define COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusComponent_h_35_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUFocusComponent(); \
	friend struct Z_Construct_UClass_UFocusComponent_Statics; \
public: \
	DECLARE_CLASS(UFocusComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FocusComponent"), NO_API) \
	DECLARE_SERIALIZER(UFocusComponent)


#define COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusComponent_h_35_INCLASS \
private: \
	static void StaticRegisterNativesUFocusComponent(); \
	friend struct Z_Construct_UClass_UFocusComponent_Statics; \
public: \
	DECLARE_CLASS(UFocusComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FocusComponent"), NO_API) \
	DECLARE_SERIALIZER(UFocusComponent)


#define COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusComponent_h_35_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UFocusComponent(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UFocusComponent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UFocusComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UFocusComponent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UFocusComponent(UFocusComponent&&); \
	NO_API UFocusComponent(const UFocusComponent&); \
public:


#define COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusComponent_h_35_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UFocusComponent(UFocusComponent&&); \
	NO_API UFocusComponent(const UFocusComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UFocusComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UFocusComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UFocusComponent)


#define COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusComponent_h_35_PRIVATE_PROPERTY_OFFSET
#define COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusComponent_h_32_PROLOG
#define COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusComponent_h_35_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusComponent_h_35_PRIVATE_PROPERTY_OFFSET \
	COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusComponent_h_35_RPC_WRAPPERS \
	COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusComponent_h_35_INCLASS \
	COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusComponent_h_35_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusComponent_h_35_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusComponent_h_35_PRIVATE_PROPERTY_OFFSET \
	COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusComponent_h_35_RPC_WRAPPERS_NO_PURE_DECLS \
	COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusComponent_h_35_INCLASS_NO_PURE_DECLS \
	COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusComponent_h_35_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FOCUSCOMPONENT_API UClass* StaticClass<class UFocusComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID COV_Plugins_PlayerPawnComponents_Source_FocusComponent_Public_FocusComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
