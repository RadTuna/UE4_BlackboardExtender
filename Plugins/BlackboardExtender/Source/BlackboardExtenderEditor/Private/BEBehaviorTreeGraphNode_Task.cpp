// Copyright Epic Games, Inc. All Rights Reserved.

#include "BEBehaviorTreeGraphNode_Task.h"
#include "BehaviorTree/BTNode.h"
#include "BEBehaviorTreeEditorTypes.h"

UBEBehaviorTreeGraphNode_Task::UBEBehaviorTreeGraphNode_Task(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UBEBehaviorTreeGraphNode_Task::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, UBEBehaviorTreeEditorTypes::PinCategory_SingleComposite, TEXT("In"));
}

FText UBEBehaviorTreeGraphNode_Task::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	const UBTNode* MyNode = Cast<UBTNode>(NodeInstance);
	if (MyNode != NULL)
	{
		return FText::FromString(MyNode->GetNodeName());
	}
	else if (!ClassData.GetClassName().IsEmpty())
	{
		FString StoredClassName = ClassData.GetClassName();
		StoredClassName.RemoveFromEnd(TEXT("_C"));

		return FText::Format(NSLOCTEXT("AIGraph", "NodeClassError", "Class {0} not found, make sure it's saved!"), FText::FromString(StoredClassName));
	}

	return Super::GetNodeTitle(TitleType);
}

void UBEBehaviorTreeGraphNode_Task::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	AddContextMenuActionsDecorators(Menu, "BehaviorTreeGraphNode", Context);
	AddContextMenuActionsServices(Menu, "BehaviorTreeGraphNode", Context);
}
