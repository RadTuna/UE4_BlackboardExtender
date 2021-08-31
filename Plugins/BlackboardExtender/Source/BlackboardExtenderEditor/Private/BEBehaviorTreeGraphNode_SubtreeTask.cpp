// Copyright 2021 RadTuna. All Rights Reserved.

#include "BEBehaviorTreeGraphNode_SubtreeTask.h"
#include "BehaviorTree/BTDecorator.h"
#include "BEBehaviorTreeDecoratorGraphNode_Decorator.h"
#include "BEBehaviorTreeGraph.h"
#include "BEBehaviorTreeGraphNode_CompositeDecorator.h"
#include "BEBehaviorTreeGraphNode_Root.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Tasks/BTTask_RunBehavior.h"

UBEBehaviorTreeGraphNode_SubtreeTask::UBEBehaviorTreeGraphNode_SubtreeTask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SubtreeVersion = 0;
}

bool UBEBehaviorTreeGraphNode_SubtreeTask::UpdateInjectedNodes()
{
	bool bUpdated = false;

	// check if cached data needs to be updated
	UBTTask_RunBehavior* MyNode = Cast<UBTTask_RunBehavior>(NodeInstance);
	if (MyNode == NULL)
	{
		return bUpdated;
	}

	UBEBehaviorTreeGraph* MyGraph = MyNode->GetSubtreeAsset() ? Cast<UBEBehaviorTreeGraph>(MyNode->GetSubtreeAsset()->BTGraph) : NULL;
	int32 MyVersion = MyGraph ? MyGraph->ModCounter : 0;
	FString MyPath = MyNode->GetSubtreeAsset() ? MyNode->GetSubtreeAsset()->GetName() : FString();

	if (MyPath == SubtreePath && MyVersion == SubtreeVersion)
	{
		return bUpdated;
	}

	SubtreePath = MyPath;
	SubtreeVersion = MyVersion;
	bUpdated = true;

	// remove existing injected nodes
	for (int32 Index = Decorators.Num() - 1; Index >= 0; Index--)
	{
		if (Decorators[Index] && Decorators[Index]->bInjectedNode)
		{
			SubNodes.RemoveSingle(Decorators[Index]);
			Decorators.RemoveAt(Index, 1, false);
		}
	}

	// find root graph node of subtree
	UBEBehaviorTreeGraphNode* SubRoot = NULL;
	if (MyGraph && MyNode->GetSubtreeAsset()->RootDecorators.Num())
	{
		for (int32 Index = 0; Index < MyGraph->Nodes.Num(); Index++)
		{
			UBEBehaviorTreeGraphNode_Root* BTNode = Cast<UBEBehaviorTreeGraphNode_Root>(MyGraph->Nodes[Index]);
			if (BTNode && BTNode->Pins.IsValidIndex(0) && BTNode->Pins[0]->LinkedTo.IsValidIndex(0))
			{
				SubRoot = Cast<UBEBehaviorTreeGraphNode>(BTNode->Pins[0]->LinkedTo[0]->GetOwningNode());
				break;
			}
		}
	}

	// add root level subnodes as injected nodes
	if (SubRoot)
	{
		UBehaviorTree* BTAsset = Cast<UBehaviorTree>(GetBehaviorTreeGraph()->GetOuter());

		if(BTAsset)
		{
			for (int32 Index = 0; Index < SubRoot->Decorators.Num(); Index++)
			{
				UBEBehaviorTreeGraphNode* SubNode = SubRoot->Decorators[Index];
				if (SubNode)
				{
					SubNode->PrepareForCopying();

					UBEBehaviorTreeGraphNode* InjectedNode = Cast<UBEBehaviorTreeGraphNode>(StaticDuplicateObject(SubNode, GetOuter()));

					SubNode->PostCopyNode();
					InjectedNode->PostCopyNode();

					InjectedNode->ParentNode = this;
					InjectedNode->bInjectedNode = true;
					InjectedNode->bIsReadOnly = true;

					UBTDecorator* InjectedInstance = Cast<UBTDecorator>(InjectedNode->NodeInstance);
					if (InjectedInstance)
					{
						InjectedInstance->InitializeFromAsset(*BTAsset);
					}

					UBEBehaviorTreeGraphNode_CompositeDecorator* CompNode = Cast<UBEBehaviorTreeGraphNode_CompositeDecorator>(InjectedNode);
					if (CompNode)
					{
						UEdGraph* SubGraph = CompNode->GetBoundGraph();
						if (SubGraph)
						{
							SubGraph->bEditable = false;

							for (int32 SubIndex = 0; SubIndex < SubGraph->Nodes.Num(); SubIndex++)
							{
								UBEBehaviorTreeDecoratorGraphNode_Decorator* InjectedDecorator = Cast<UBEBehaviorTreeDecoratorGraphNode_Decorator>(SubGraph->Nodes[SubIndex]);
								if (InjectedDecorator)
								{
									InjectedInstance = Cast<UBTDecorator>(InjectedDecorator->NodeInstance);
									if (InjectedInstance)
									{
										InjectedInstance->InitializeFromAsset(*BTAsset);
									}
								}
							}
						}
					}

					SubNodes.Add(InjectedNode);
					Decorators.Add(InjectedNode);
				}
			}
		}
	}

	UEdGraph* ParentGraph = GetGraph();
	if (ParentGraph && bUpdated)
	{
		ParentGraph->NotifyGraphChanged();
	}

	return bUpdated;
}
