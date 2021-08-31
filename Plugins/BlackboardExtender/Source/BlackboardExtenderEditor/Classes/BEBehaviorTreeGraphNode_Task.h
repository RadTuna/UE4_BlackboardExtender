// Copyright 2021 RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "BEBehaviorTreeGraphNode.h"
#include "BEBehaviorTreeGraphNode_Task.generated.h"

UCLASS()
class UBEBehaviorTreeGraphNode_Task : public UBEBehaviorTreeGraphNode
{
	GENERATED_UCLASS_BODY()

	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	/** Gets a list of actions that can be done to this particular node */
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;

	virtual bool CanPlaceBreakpoints() const override { return true; }
};
