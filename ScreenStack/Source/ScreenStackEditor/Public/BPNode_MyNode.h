#pragma once
#include "K2Node.h"
#include "K2Node_ConstructObjectFromClass.h"
#include "BPNode_MyNode.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SCREENSTACKEDITOR_API UBPNode_PushScreenByClass : public UK2Node_ConstructObjectFromClass
{
    GENERATED_UCLASS_BODY()

    // Begin UEdGraphNode interface.
    virtual void AllocateDefaultPins() override;
    virtual FLinearColor GetNodeTitleColor() const override;
    //this is where node will be expanded with additional pins!
    virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
    // End UEdGraphNode interface.

    virtual FText GetMenuCategory() const override;
    // End UK2Node interface.

    /** Get the owning player pin */
    UEdGraphPin* GetOwningPlayerPin() const;

protected:
    /** Gets the default node title when no class is selected */
    virtual FText GetBaseNodeTitle() const;
    /** Gets the node title when a class has been selected. */
    virtual FText GetNodeTitleFormat() const;
    /** Gets base class to use for the 'class' pin.  UObject by default. */
    virtual UClass* GetClassPinBaseClass() const;
    virtual bool IsSpawnVarPin(UEdGraphPin* Pin) const override;

};