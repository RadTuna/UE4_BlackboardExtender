// Copyright 2021 RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "BEBehaviorTreeGraphNode.h"
#include "BEBehaviorTreeGraphNode_Composite.generated.h"

UCLASS()
class BLACKBOARDEXTENDEREDITOR_API UBEBehaviorTreeGraphNode_Composite : public UBEBehaviorTreeGraphNode
{
	GENERATED_UCLASS_BODY()
	
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetDescription() const override;
	virtual FText GetTooltipText() const override;
	virtual bool RefreshNodeClass() override{ return false; }

	/** Gets a list of actions that can be done to this particular node */
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;

	/** check if node can accept breakpoints */
	virtual bool CanPlaceBreakpoints() const override { return true; }
};
