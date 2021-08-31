// Copyright 2021 RadTuna. All Rights Reserved.
#include "BEBehaviorTreeDecoratorGraph.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/BTCompositeNode.h"
#include "BEBehaviorTreeDecoratorGraphNode.h"
#include "BEBehaviorTreeDecoratorGraphNode_Decorator.h"
#include "BEBehaviorTreeDecoratorGraphNode_Logic.h"
#include "EdBEGraphSchema_BehaviorTreeDecorator.h"

//////////////////////////////////////////////////////////////////////////
// BehaviorTreeGraph

UBEBehaviorTreeDecoratorGraph::UBEBehaviorTreeDecoratorGraph(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Schema = UEdBEGraphSchema_BehaviorTreeDecorator::StaticClass();
}

void UBEBehaviorTreeDecoratorGraph::CollectDecoratorData(TArray<UBTDecorator*>& DecoratorInstances, TArray<FBTDecoratorLogic>& DecoratorOperations) const
{
	const UBEBehaviorTreeDecoratorGraphNode* RootNode = FindRootNode();
	CollectDecoratorDataWorker(RootNode, DecoratorInstances, DecoratorOperations);
}

const UBEBehaviorTreeDecoratorGraphNode* UBEBehaviorTreeDecoratorGraph::FindRootNode() const
{
	for (int32 i = 0; i < Nodes.Num(); i++)
	{
		const UBEBehaviorTreeDecoratorGraphNode_Logic* TestNode = Cast<const UBEBehaviorTreeDecoratorGraphNode_Logic>(Nodes[i]);
		if (TestNode && TestNode->LogicMode == EBEDecoratorLogicMode::Sink)
		{
			return TestNode;
		}
	}

	return NULL;
}

void UBEBehaviorTreeDecoratorGraph::CollectDecoratorDataWorker(const UBEBehaviorTreeDecoratorGraphNode* Node,
															 TArray<UBTDecorator*>& DecoratorInstances, TArray<FBTDecoratorLogic>& DecoratorOperations) const
{
	if (Node == NULL)
	{
		return;
	}

	TArray<const UBEBehaviorTreeDecoratorGraphNode*> LinkedNodes;
	for (int32 i = 0; i < Node->Pins.Num(); i++)
	{
		if (Node->Pins[i]->Direction == EGPD_Input &&
			Node->Pins[i]->LinkedTo.Num() > 0)
		{
			const UBEBehaviorTreeDecoratorGraphNode* LinkedNode = Cast<const UBEBehaviorTreeDecoratorGraphNode>(Node->Pins[i]->LinkedTo[0]->GetOwningNode());
			if (LinkedNode)
			{
				LinkedNodes.Add(LinkedNode);
			}
		}
	}

	FBTDecoratorLogic LogicOp(Node->GetOperationType(), LinkedNodes.Num());

	// special case: invalid
	if (LogicOp.Operation == EBTDecoratorLogic::Invalid)
	{
		// discard
	}
	// special case: test
	else if (LogicOp.Operation == EBTDecoratorLogic::Test)
	{
		// add decorator instance
		const UBEBehaviorTreeDecoratorGraphNode_Decorator* DecoratorNode = Cast<const UBEBehaviorTreeDecoratorGraphNode_Decorator>(Node);
		UBTDecorator* DecoratorInstance = DecoratorNode ? (UBTDecorator*)DecoratorNode->NodeInstance : NULL;
		if (DecoratorInstance)
		{
			LogicOp.Number = DecoratorInstances.Add(DecoratorInstance);
			DecoratorOperations.Add(LogicOp);
		}
	}
	else
	{
		DecoratorOperations.Add(LogicOp);
	}

	for (int32 i = 0; i < LinkedNodes.Num(); i++)
	{
		CollectDecoratorDataWorker(LinkedNodes[i], DecoratorInstances, DecoratorOperations);
	}
}

UEdGraphPin* UBEBehaviorTreeDecoratorGraph::FindFreePin(UEdGraphNode* Node, EEdGraphPinDirection Direction)
{
	for (int32 Idx = 0; Idx < Node->Pins.Num(); Idx++)
	{
		if (Node->Pins[Idx] && Node->Pins[Idx]->Direction == Direction && Node->Pins[Idx]->LinkedTo.Num() == 0)
		{
			return Node->Pins[Idx];
		}
	}

	return nullptr;
}

UBEBehaviorTreeDecoratorGraphNode* UBEBehaviorTreeDecoratorGraph::SpawnMissingNodeWorker(const TArray<class UBTDecorator*>& NodeInstances, const TArray<struct FBTDecoratorLogic>& Operations, int32& Index, UEdGraphNode* ParentGraphNode, int32 ChildIdx)
{
	int32 NumSteps = 0;
	UBEBehaviorTreeDecoratorGraphNode* GraphNode = nullptr;
	UBEBehaviorTreeDecoratorGraphNode_Logic* LogicNode = nullptr;

	const FBTDecoratorLogic& Op = Operations[Index];
	Index++;

	if (Op.Operation == EBTDecoratorLogic::Test)
	{
		FGraphNodeCreator<UBEBehaviorTreeDecoratorGraphNode_Decorator> NodeBuilder(*this);
		UBEBehaviorTreeDecoratorGraphNode_Decorator* CastedGraphNode = NodeBuilder.CreateNode();
		NodeBuilder.Finalize();

		GraphNode = CastedGraphNode;
		CastedGraphNode->NodeInstance = NodeInstances[Op.Number];
	}
	else
	{
		FGraphNodeCreator<UBEBehaviorTreeDecoratorGraphNode_Logic> NodeBuilder(*this);
		LogicNode = NodeBuilder.CreateNode();
		LogicNode->LogicMode = LogicNode->GetLogicMode(Op.Operation);
		NodeBuilder.Finalize();

		GraphNode = LogicNode;
		NumSteps = Op.Number;
	}

	if (GraphNode)
	{
		GraphNode->NodePosX = ParentGraphNode->NodePosX - 300.0f;
		GraphNode->NodePosY = ParentGraphNode->NodePosY + ChildIdx * 100.0f;
	}

	for (int32 Idx = 0; Idx < NumSteps; Idx++)
	{
		UBEBehaviorTreeDecoratorGraphNode* ChildNode = SpawnMissingNodeWorker(NodeInstances, Operations, Index, GraphNode, Idx);

		UEdGraphPin* ChildOut = FindFreePin(ChildNode, EGPD_Output);
		UEdGraphPin* NodeIn = FindFreePin(GraphNode, EGPD_Input);
		
		if (NodeIn == nullptr && LogicNode)
		{
			NodeIn = LogicNode->AddInputPin();
		}

		if (NodeIn && ChildOut)
		{
			NodeIn->MakeLinkTo(ChildOut);
		}
	}

	return GraphNode;
}

int32 UBEBehaviorTreeDecoratorGraph::SpawnMissingNodes(const TArray<class UBTDecorator*>& NodeInstances, const TArray<struct FBTDecoratorLogic>& Operations, int32 StartIndex)
{
	UBEBehaviorTreeDecoratorGraphNode* RootNode = nullptr;
	for (int32 Idx = 0; Idx < Nodes.Num(); Idx++)
	{
		UBEBehaviorTreeDecoratorGraphNode_Logic* TestNode = Cast<UBEBehaviorTreeDecoratorGraphNode_Logic>(Nodes[Idx]);
		if (TestNode && TestNode->LogicMode == EBEDecoratorLogicMode::Sink)
		{
			RootNode = TestNode;
			break;
		}
	}

	int32 NextIndex = StartIndex;
	if (RootNode)
	{
		UBEBehaviorTreeDecoratorGraphNode* OperationRoot = SpawnMissingNodeWorker(NodeInstances, Operations, NextIndex, RootNode, 0);
		if (OperationRoot)
		{
			UEdGraphPin* RootIn = FindFreePin(RootNode, EGPD_Input);
			UEdGraphPin* OpOut = FindFreePin(OperationRoot, EGPD_Output);

			RootIn->MakeLinkTo(OpOut);
		}
	}
	else
	{
		NextIndex++;
	}

	return NextIndex;
}
