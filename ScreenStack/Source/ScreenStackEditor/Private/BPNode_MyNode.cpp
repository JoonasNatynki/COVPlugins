// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#include "BPNode_MyNode.h"
#include "COVEditorRuntime.h"
#include "COVEditorItemData.h"
#include "KismetCompiler.h"
#include "BlueprintNodeSpawner.h"
#include "EditorCategoryUtils.h"
#include "BlueprintActionDatabase.h"
#include "KismetCompilerMisc.h"
#include "EdGraphSchema_K2.h"
#include "K2Node_CallFunction.h"
#include "Blueprint/UserWidget.h"

#define LOCTEXT_NAMESPACE "GameInventorySystem"

//Helper which will store one of the function inputs we expect BP callable function will have.
struct FBPNode_CreateItemDataHelper
{
	static FName OwningPlayerPinName;
};

FName FBPNode_CreateItemDataHelper::OwningPlayerPinName(TEXT("OwningPlayer"));

UBPNode_PushScreenByClass::UBPNode_PushScreenByClass(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeTooltip = LOCTEXT("NodeTooltip", "Pushes a new screen into the screen stack");
}

//Adds default pins to node. These Pins (inputs ?) are always displayed.
void UBPNode_PushScreenByClass::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// OwningPlayer pin
	UEdGraphPin* OwningPlayerPin = CreatePin(EGPD_Input, TEXT(""), FBPNode_CreateItemDataHelper::OwningPlayerPinName);
	SetPinToolTip(*OwningPlayerPin, LOCTEXT("OwningPlayerPinDescription", "The player that 'owns' the this item."));
}

FLinearColor UBPNode_PushScreenByClass::GetNodeTitleColor() const
{
	return Super::GetNodeTitleColor();
}

FText UBPNode_PushScreenByClass::GetBaseNodeTitle() const
{
	return LOCTEXT("CreateItemData_BaseTitle", "Push screen by class");
}

FText UBPNode_PushScreenByClass::GetNodeTitleFormat() const
{
	return LOCTEXT("CreateItemData", "Create and push {ClassName} into the screen stack");
}

//which class can be used with this node to create objects. All childes of class can be used.
UClass* UBPNode_PushScreenByClass::GetClassPinBaseClass() const
{
	return UUserWidget::StaticClass();
}

//Set context menu category in which our node will be present.
FText UBPNode_PushScreenByClass::GetMenuCategory() const
{
	return FText::FromString("Screen stack");
}

//gets out predefined pin
UEdGraphPin* UBPNode_PushScreenByClass::GetOwningPlayerPin() const
{
	UEdGraphPin* Pin = FindPin(FBPNode_CreateItemDataHelper::OwningPlayerPinName);
	check(Pin == NULL || Pin->Direction == EGPD_Input);
	return Pin;
}

bool UBPNode_PushScreenByClass::IsSpawnVarPin(UEdGraphPin* Pin) const
{
	return(Super::IsSpawnVarPin(Pin) &&
		Pin->PinName != FBPNode_CreateItemDataHelper::OwningPlayerPinName);
}

//and this is where magic really happens. This will expand node for our custom object, with properties
//which are set as EditAwnywhere and meta=(ExposeOnSpawn), or equivalent in blueprint.
void UBPNode_PushScreenByClass::ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	static const FName Create_FunctionName = GET_FUNCTION_NAME_CHECKED(UCOVEditorRuntimeLibrary, Create);
	static const FName WorldContextObject_ParamName(TEXT("WorldContextObject"));
	static const FName WidgetType_ParamName(TEXT("WidgetType"));
	static const FName OwningPlayer_ParamName(TEXT("OwningPlayer"));

	UBPNode_PushScreenByClass* PushScreenByClassNode = this;
	UEdGraphPin* SpawnNodeExec = PushScreenByClassNode->GetExecPin();
	UEdGraphPin* SpawnWorldContextPin = PushScreenByClassNode->GetWorldContextPin();
	UEdGraphPin* SpawnOwningPlayerPin = PushScreenByClassNode->GetOwningPlayerPin();
	UEdGraphPin* SpawnClassPin = PushScreenByClassNode->GetClassPin();
	UEdGraphPin* SpawnNodeThen = PushScreenByClassNode->GetThenPin();
	UEdGraphPin* SpawnNodeResult = PushScreenByClassNode->GetResultPin();

	UClass* SpawnClass = (SpawnClassPin != NULL) ? Cast<UClass>(SpawnClassPin->DefaultObject) : NULL;
	if (!SpawnClassPin || ((0 == SpawnClassPin->LinkedTo.Num()) && (NULL == SpawnClass)))
	{
		CompilerContext.MessageLog.Error(*LOCTEXT("CreateWidgetNodeMissingClass_Error", "Spawn node @@ must have a class specified.").ToString(), PushScreenByClassNode);
		// we break exec links so this is the only error we get, don't want the CreateWidget node being considered and giving 'unexpected node' type warnings
		PushScreenByClassNode->BreakAllNodeLinks();
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	// create 'UWidgetBlueprintLibrary::Create' call node
	UK2Node_CallFunction* CallCreateNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(PushScreenByClassNode, SourceGraph);
	CallCreateNode->FunctionReference.SetExternalMember(Create_FunctionName, UCOVEditorRuntimeLibrary::StaticClass());
	CallCreateNode->AllocateDefaultPins();

	// store off the class to spawn before we mutate pin connections:
	UClass* ClassToSpawn = GetClassToSpawn();

	UEdGraphPin* CallCreateExec = CallCreateNode->GetExecPin();
	UEdGraphPin* CallCreateWorldContextPin = CallCreateNode->FindPinChecked(WorldContextObject_ParamName);
	UEdGraphPin* CallCreateWidgetTypePin = CallCreateNode->FindPinChecked(WidgetType_ParamName);
	UEdGraphPin* CallCreateOwningPlayerPin = CallCreateNode->FindPinChecked(OwningPlayer_ParamName);
	UEdGraphPin* CallCreateResult = CallCreateNode->GetReturnValuePin();

	// Move 'exec' connection from create widget node to 'UWidgetBlueprintLibrary::Create'
	CompilerContext.MovePinLinksToIntermediate(*SpawnNodeExec, *CallCreateExec);

	if (SpawnClassPin->LinkedTo.Num() > 0)
	{
		// Copy the 'blueprint' connection from the spawn node to 'UWidgetBlueprintLibrary::Create'
		CompilerContext.MovePinLinksToIntermediate(*SpawnClassPin, *CallCreateWidgetTypePin);
	}
	else
	{
		// Copy blueprint literal onto 'UWidgetBlueprintLibrary::Create' call
		CallCreateWidgetTypePin->DefaultObject = SpawnClass;
	}

	// Copy the world context connection from the spawn node to 'UWidgetBlueprintLibrary::Create' if necessary
	if (SpawnWorldContextPin)
	{
		CompilerContext.MovePinLinksToIntermediate(*SpawnWorldContextPin, *CallCreateWorldContextPin);
	}

	// Copy the 'Owning Player' connection from the spawn node to 'UWidgetBlueprintLibrary::Create'
	CompilerContext.MovePinLinksToIntermediate(*SpawnOwningPlayerPin, *CallCreateOwningPlayerPin);

	// Move result connection from spawn node to 'UWidgetBlueprintLibrary::Create'
	CallCreateResult->PinType = SpawnNodeResult->PinType; // Copy type so it uses the right actor subclass
	CompilerContext.MovePinLinksToIntermediate(*SpawnNodeResult, *CallCreateResult);

	//////////////////////////////////////////////////////////////////////////
	// create 'set var' nodes

	// Get 'result' pin from 'begin spawn', this is the actual actor we want to set properties on
	UEdGraphPin* LastThen = FKismetCompilerUtilities::GenerateAssignmentNodes(CompilerContext, SourceGraph, CallCreateNode, PushScreenByClassNode, CallCreateResult, ClassToSpawn);

	// Move 'then' connection from create widget node to the last 'then'
	CompilerContext.MovePinLinksToIntermediate(*SpawnNodeThen, *LastThen);

	// Break any links to the expanded node
	PushScreenByClassNode->BreakAllNodeLinks();
}

#undef LOCTEXT_NAMESPACE
