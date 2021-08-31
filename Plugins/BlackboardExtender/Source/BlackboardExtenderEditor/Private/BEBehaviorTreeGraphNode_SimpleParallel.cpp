// Copyright 2021 RadTuna. All Rights Reserved.

#include "BEBehaviorTreeGraphNode_SimpleParallel.h"
#include "BEBehaviorTreeEditorTypes.h"

#define LOCTEXT_NAMESPACE "BlackboardExtenderEditor"

UBEBehaviorTreeGraphNode_SimpleParallel::UBEBehaviorTreeGraphNode_SimpleParallel(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UBEBehaviorTreeGraphNode_SimpleParallel::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, UBEBehaviorTreeEditorTypes::PinCategory_MultipleNodes, TEXT("In"));
	
	CreatePin(EGPD_Output, UBEBehaviorTreeEditorTypes::PinCategory_SingleTask, TEXT("Task"));
	CreatePin(EGPD_Output, UBEBehaviorTreeEditorTypes::PinCategory_SingleNode, TEXT("Out"));
}

void UBEBehaviorTreeGraphNode_SimpleParallel::GetPinHoverText(const UEdGraphPin& Pin, FString& HoverTextOut) const
{
	ensure(Pin.GetOwningNode() == this);
	if (Pin.Direction == EGPD_Output)
	{
		if (Pin.PinType.PinCategory == UBEBehaviorTreeEditorTypes::PinCategory_SingleTask)
		{
			HoverTextOut = LOCTEXT("PinHoverParallelMain","Main task of parrallel node").ToString();
		}
		else
		{
			HoverTextOut = LOCTEXT("PinHoverParallelBackground","Nodes running in the background, while main task is active").ToString();
		}
	}
}

#undef LOCTEXT_NAMESPACE
