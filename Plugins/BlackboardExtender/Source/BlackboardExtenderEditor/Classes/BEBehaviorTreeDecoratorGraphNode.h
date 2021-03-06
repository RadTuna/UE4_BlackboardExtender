// Copyright 2021 RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EdGraph/EdGraphNode.h"
#include "BehaviorTree/BTCompositeNode.h"
#include "BEBehaviorTreeDecoratorGraphNode.generated.h"

class UEdGraphSchema;

UCLASS()
class UBEBehaviorTreeDecoratorGraphNode : public UEdGraphNode
{
	GENERATED_UCLASS_BODY()

	/** Get the BT graph that owns this node */
	virtual class UBEBehaviorTreeDecoratorGraph* GetDecoratorGraph();

	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;

	// @return the input pin for this state
	virtual UEdGraphPin* GetInputPin(int32 InputIndex=0) const;
	// @return the output pin for this state
	virtual UEdGraphPin* GetOutputPin(int32 InputIndex=0) const;

	virtual EBTDecoratorLogic::Type GetOperationType() const;

	/** allow creating / removing inputs */
	uint32 bAllowModifingInputs : 1;

	virtual void NodeConnectionListChanged() override;

	virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* DesiredSchema) const override;

	virtual bool CanUserDeleteNode() const override;
};
