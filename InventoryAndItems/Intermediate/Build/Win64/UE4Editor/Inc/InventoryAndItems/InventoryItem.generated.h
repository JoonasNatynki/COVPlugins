// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FGuid;
#ifdef INVENTORYANDITEMS_InventoryItem_generated_h
#error "InventoryItem.generated.h already included, missing '#pragma once' in InventoryItem.h"
#endif
#define INVENTORYANDITEMS_InventoryItem_generated_h

#define COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_InventoryItem_h_10_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execSetItemGUID) \
	{ \
		P_GET_STRUCT(FGuid,Z_Param_itemGuid); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetItemGUID(Z_Param_itemGuid); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetItemGUID) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FGuid*)Z_Param__Result=P_THIS->GetItemGUID(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execOnRep_ItemGUID) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnRep_ItemGUID(); \
		P_NATIVE_END; \
	}


#define COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_InventoryItem_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSetItemGUID) \
	{ \
		P_GET_STRUCT(FGuid,Z_Param_itemGuid); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->SetItemGUID(Z_Param_itemGuid); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetItemGUID) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FGuid*)Z_Param__Result=P_THIS->GetItemGUID(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execOnRep_ItemGUID) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnRep_ItemGUID(); \
		P_NATIVE_END; \
	}


#define COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_InventoryItem_h_10_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUInventoryItemComponent(); \
	friend struct Z_Construct_UClass_UInventoryItemComponent_Statics; \
public: \
	DECLARE_CLASS(UInventoryItemComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/InventoryAndItems"), NO_API) \
	DECLARE_SERIALIZER(UInventoryItemComponent)


#define COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_InventoryItem_h_10_INCLASS \
private: \
	static void StaticRegisterNativesUInventoryItemComponent(); \
	friend struct Z_Construct_UClass_UInventoryItemComponent_Statics; \
public: \
	DECLARE_CLASS(UInventoryItemComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/InventoryAndItems"), NO_API) \
	DECLARE_SERIALIZER(UInventoryItemComponent)


#define COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_InventoryItem_h_10_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UInventoryItemComponent(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UInventoryItemComponent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UInventoryItemComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInventoryItemComponent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UInventoryItemComponent(UInventoryItemComponent&&); \
	NO_API UInventoryItemComponent(const UInventoryItemComponent&); \
public:


#define COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_InventoryItem_h_10_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UInventoryItemComponent(UInventoryItemComponent&&); \
	NO_API UInventoryItemComponent(const UInventoryItemComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UInventoryItemComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInventoryItemComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UInventoryItemComponent)


#define COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_InventoryItem_h_10_PRIVATE_PROPERTY_OFFSET
#define COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_InventoryItem_h_7_PROLOG
#define COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_InventoryItem_h_10_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_InventoryItem_h_10_PRIVATE_PROPERTY_OFFSET \
	COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_InventoryItem_h_10_RPC_WRAPPERS \
	COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_InventoryItem_h_10_INCLASS \
	COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_InventoryItem_h_10_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_InventoryItem_h_10_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_InventoryItem_h_10_PRIVATE_PROPERTY_OFFSET \
	COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_InventoryItem_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
	COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_InventoryItem_h_10_INCLASS_NO_PURE_DECLS \
	COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_InventoryItem_h_10_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> INVENTORYANDITEMS_API UClass* StaticClass<class UInventoryItemComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_InventoryItem_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
