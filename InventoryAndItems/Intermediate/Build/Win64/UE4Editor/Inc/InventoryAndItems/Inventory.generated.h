// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UInventoryItemComponent;
class AActor;
class UObject;
#ifdef INVENTORYANDITEMS_Inventory_generated_h
#error "Inventory.generated.h already included, missing '#pragma once' in Inventory.h"
#endif
#define INVENTORYANDITEMS_Inventory_generated_h

#define COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_Inventory_h_10_DELEGATE \
struct _Script_InventoryAndItems_eventOnItemAdded_Parms \
{ \
	UInventoryItemComponent* InventoryItem; \
}; \
static inline void FOnItemAdded_DelegateWrapper(const FMulticastScriptDelegate& OnItemAdded, UInventoryItemComponent* InventoryItem) \
{ \
	_Script_InventoryAndItems_eventOnItemAdded_Parms Parms; \
	Parms.InventoryItem=InventoryItem; \
	OnItemAdded.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_Inventory_h_15_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnRep_Inventory) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnRep_Inventory(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRemoveItem) \
	{ \
		P_GET_OBJECT(AActor,Z_Param_item); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->RemoveItem(Z_Param_item); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddItem) \
	{ \
		P_GET_OBJECT(AActor,Z_Param_item); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->AddItem(Z_Param_item); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execTransferInventoryDataToObject) \
	{ \
		P_GET_OBJECT(UObject,Z_Param_fromObject); \
		P_GET_OBJECT(UObject,Z_Param_toObject); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->TransferInventoryDataToObject(Z_Param_fromObject,Z_Param_toObject); \
		P_NATIVE_END; \
	}


#define COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_Inventory_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnRep_Inventory) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnRep_Inventory(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRemoveItem) \
	{ \
		P_GET_OBJECT(AActor,Z_Param_item); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->RemoveItem(Z_Param_item); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execAddItem) \
	{ \
		P_GET_OBJECT(AActor,Z_Param_item); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->AddItem(Z_Param_item); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execTransferInventoryDataToObject) \
	{ \
		P_GET_OBJECT(UObject,Z_Param_fromObject); \
		P_GET_OBJECT(UObject,Z_Param_toObject); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->TransferInventoryDataToObject(Z_Param_fromObject,Z_Param_toObject); \
		P_NATIVE_END; \
	}


#define COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_Inventory_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUInventoryComponent(); \
	friend struct Z_Construct_UClass_UInventoryComponent_Statics; \
public: \
	DECLARE_CLASS(UInventoryComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/InventoryAndItems"), NO_API) \
	DECLARE_SERIALIZER(UInventoryComponent)


#define COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_Inventory_h_15_INCLASS \
private: \
	static void StaticRegisterNativesUInventoryComponent(); \
	friend struct Z_Construct_UClass_UInventoryComponent_Statics; \
public: \
	DECLARE_CLASS(UInventoryComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/InventoryAndItems"), NO_API) \
	DECLARE_SERIALIZER(UInventoryComponent)


#define COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_Inventory_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UInventoryComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UInventoryComponent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UInventoryComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInventoryComponent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UInventoryComponent(UInventoryComponent&&); \
	NO_API UInventoryComponent(const UInventoryComponent&); \
public:


#define COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_Inventory_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UInventoryComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UInventoryComponent(UInventoryComponent&&); \
	NO_API UInventoryComponent(const UInventoryComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UInventoryComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInventoryComponent); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UInventoryComponent)


#define COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_Inventory_h_15_PRIVATE_PROPERTY_OFFSET
#define COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_Inventory_h_12_PROLOG
#define COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_Inventory_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_Inventory_h_15_PRIVATE_PROPERTY_OFFSET \
	COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_Inventory_h_15_RPC_WRAPPERS \
	COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_Inventory_h_15_INCLASS \
	COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_Inventory_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_Inventory_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_Inventory_h_15_PRIVATE_PROPERTY_OFFSET \
	COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_Inventory_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_Inventory_h_15_INCLASS_NO_PURE_DECLS \
	COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_Inventory_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> INVENTORYANDITEMS_API UClass* StaticClass<class UInventoryComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID COV_Plugins_InventoryAndItems_Source_InventoryAndItems_Public_Inventory_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
