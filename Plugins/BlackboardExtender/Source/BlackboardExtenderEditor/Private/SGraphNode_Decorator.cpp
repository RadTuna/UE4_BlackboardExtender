// Copyright 2021 RadTuna. All Rights Reserved.

#include "SGraphNode_Decorator.h"
#include "BehaviorTree/BTDecorator.h"
#include "BEBehaviorTreeDecoratorGraphNode_Decorator.h"

void SGraphNode_Decorator::Construct(const FArguments& InArgs, UBEBehaviorTreeDecoratorGraphNode_Decorator* InNode)
{
	this->GraphNode = InNode;

	this->SetCursor(EMouseCursor::CardinalCross);

	this->UpdateGraphNode();
}

FString SGraphNode_Decorator::GetNodeComment() const
{
	const UBEBehaviorTreeDecoratorGraphNode_Decorator* MyGraphNode = Cast<const UBEBehaviorTreeDecoratorGraphNode_Decorator>(GetNodeObj());
	const UBTDecorator* MyBTNode = MyGraphNode ? Cast<const UBTDecorator>(MyGraphNode->NodeInstance) : NULL;

	if (MyBTNode)
	{
		return MyBTNode->GetNodeName();
	}

	return SGraphNode::GetNodeComment();
}
