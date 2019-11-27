// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class USceneComponent;
#ifdef GAMEPLAYOBJECTCOMPONENTS_HoveringMotion_generated_h
#error "HoveringMotion.generated.h already included, missing '#pragma once' in HoveringMotion.h"
#endif
#define GAMEPLAYOBJECTCOMPONENTS_HoveringMotion_generated_h

#define COV_Plugins_GameplayObjectComponents_Source_GameplayObjectComponents_Public_HoveringMotion_h_14_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execIsHoverComponentRootComponent) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->IsHoverComponentRootComponent(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSetAnimating) \
	{ \
		P_GET_UBOOL(Z_Param_bShouldAnimate); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetAnimating(Z_Param_bShouldAnimate); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSetHoveringComponent) \
	{ \
		P_GET_OBJECT(USceneComponent,Z_Param__componentToHover); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetHoveringComponent(Z_Param__componentToHover); \
		P_NATIVE_END; \
	}


#define COV_Plugins_GameplayObjectComponents_Source_GameplayObjectComponents_Public_HoveringMotion_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execIsHoverComponentRootComponent) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->IsHoverComponentRootComponent(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSetAnimating) \
	{ \
		P_GET_UBOOL(Z_Param_bShouldAnimate); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetAnimating(Z_Param_bShouldAnimate); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execSetHoveringComponent) \
	{ \
		P_GET_OBJECT(USceneComponent,Z_Param__componentToHover); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetHoveringComponent(Z_Param__componentToHover); \
		P_NATIVE_END; \
	}


#define COV_Plugins_GameplayObjectComponents_Source_GameplayObjectComponents_Public_HoveringMotion_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUHoveringMotion(); \
	friend struct Z_Construct_UClass_UHoveringMotion_Statics; \
public: \
	DECLARE_CLASS(UHoveringMotion, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/GameplayObjectComponents"), NO_API) \
	DECLARE_SERIALIZER(UHoveringMotion)


#define COV_Plugins_GameplayObjectComponents_Source_GameplayObjectComponents_Public_HoveringMotion_h_14_INCLASS \
private: \
	static void StaticRegisterNativesUHoveringMotion(); \
	friend struct Z_Construct_UClass_UHoveringMotion_Statics; \
public: \
	DECLARE_CLASS(UHoveringMotion, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/GameplayObjectComponents"), NO_API) \
	DECLARE_SERIALIZER(UHoveringMotion)


#define COV_Plugins_GameplayObjectComponents_Source_GameplayObjectComponents_Public_HoveringMotion_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UHoveringMotion(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UHoveringMotion) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UHoveringMotion); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UHoveringMotion); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UHoveringMotion(UHoveringMotion&&); \
	NO_API UHoveringMotion(const UHoveringMotion&); \
public:


#define COV_Plugins_GameplayObjectComponents_Source_GameplayObjectComponents_Public_HoveringMotion_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UHoveringMotion(UHoveringMotion&&); \
	NO_API UHoveringMotion(const UHoveringMotion&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UHoveringMotion); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UHoveringMotion); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UHoveringMotion)


#define COV_Plugins_GameplayObjectComponents_Source_GameplayObjectComponents_Public_HoveringMotion_h_14_PRIVATE_PROPERTY_OFFSET
#define COV_Plugins_GameplayObjectComponents_Source_GameplayObjectComponents_Public_HoveringMotion_h_11_PROLOG
#define COV_Plugins_GameplayObjectComponents_Source_GameplayObjectComponents_Public_HoveringMotion_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	COV_Plugins_GameplayObjectComponents_Source_GameplayObjectComponents_Public_HoveringMotion_h_14_PRIVATE_PROPERTY_OFFSET \
	COV_Plugins_GameplayObjectComponents_Source_GameplayObjectComponents_Public_HoveringMotion_h_14_RPC_WRAPPERS \
	COV_Plugins_GameplayObjectComponents_Source_GameplayObjectComponents_Public_HoveringMotion_h_14_INCLASS \
	COV_Plugins_GameplayObjectComponents_Source_GameplayObjectComponents_Public_HoveringMotion_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define COV_Plugins_GameplayObjectComponents_Source_GameplayObjectComponents_Public_HoveringMotion_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	COV_Plugins_GameplayObjectComponents_Source_GameplayObjectComponents_Public_HoveringMotion_h_14_PRIVATE_PROPERTY_OFFSET \
	COV_Plugins_GameplayObjectComponents_Source_GameplayObjectComponents_Public_HoveringMotion_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	COV_Plugins_GameplayObjectComponents_Source_GameplayObjectComponents_Public_HoveringMotion_h_14_INCLASS_NO_PURE_DECLS \
	COV_Plugins_GameplayObjectComponents_Source_GameplayObjectComponents_Public_HoveringMotion_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> GAMEPLAYOBJECTCOMPONENTS_API UClass* StaticClass<class UHoveringMotion>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID COV_Plugins_GameplayObjectComponents_Source_GameplayObjectComponents_Public_HoveringMotion_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
