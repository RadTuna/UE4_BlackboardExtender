// Copyright 2021 RadTuna. All Rights Reserved.

#include "BEBehaviorTreeGraphNode_CompositeDecorator.h"
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/BTCompositeNode.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "BEBehaviorTreeDecoratorGraph.h"
#include "BEBehaviorTreeDecoratorGraphNode_Decorator.h"
#include "EdBEGraphSchema_BehaviorTreeDecorator.h"
#include "BehaviorTree/BehaviorTree.h"

#define LOCTEXT_NAMESPACE "BlackboardExtenderEditor"

UBEBehaviorTreeGraphNode_CompositeDecorator::UBEBehaviorTreeGraphNode_CompositeDecorator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bShowOperations = true;
	bCanAbortFlow = false;
	bHasBrokenInstances = false;

	FirstExecutionIndex = INDEX_NONE;
	LastExecutionIndex = INDEX_NONE;
}

void UBEBehaviorTreeGraphNode_CompositeDecorator::ResetExecutionRange()
{
	FirstExecutionIndex = INDEX_NONE;
	LastExecutionIndex = INDEX_NONE;
}

void UBEBehaviorTreeGraphNode_CompositeDecorator::AllocateDefaultPins()
{
	// No Pins for decorators
}

FString UBEBehaviorTreeGraphNode_CompositeDecorator::GetNodeTypeDescription() const
{
	return LOCTEXT("Composite","Composite").ToString();
}

FText UBEBehaviorTreeGraphNode_CompositeDecorator::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(CompositeName.Len() ? CompositeName : GetNodeTypeDescription());
}

FText UBEBehaviorTreeGraphNode_CompositeDecorator::GetDescription() const
{
	return FText::FromString(CachedDescription);
}

void UBEBehaviorTreeGraphNode_CompositeDecorator::PostPlacedNewNode()
{
	if (BoundGraph == nullptr)
	{
		CreateBoundGraph();
	}

	Super::PostPlacedNewNode();
}

void UBEBehaviorTreeGraphNode_CompositeDecorator::PostLoad()
{
	Super::PostLoad();

	if (BoundGraph == nullptr)
	{
		CreateBoundGraph();
	}
}

void UBEBehaviorTreeGraphNode_CompositeDecorator::PrepareForCopying()
{
	Super::PrepareForCopying();
	
	if (BoundGraph)
	{
		for (int32 i = 0; i < BoundGraph->Nodes.Num(); i++)
		{
			UEdGraphNode* Node = BoundGraph->Nodes[i];
			Node->PrepareForCopying();
		}
	}
}

void UBEBehaviorTreeGraphNode_CompositeDecorator::PostCopyNode()
{
	Super::PostCopyNode();

	if (BoundGraph)
	{
		for (int32 i = 0; i < BoundGraph->Nodes.Num(); i++)
		{
			UBEBehaviorTreeDecoratorGraphNode_Decorator* Node = Cast<UBEBehaviorTreeDecoratorGraphNode_Decorator>(BoundGraph->Nodes[i]);
			if (Node)
			{
				Node->PostCopyNode();
			}
		}
	}
}

void UBEBehaviorTreeGraphNode_CompositeDecorator::ResetNodeOwner()
{
	Super::ResetNodeOwner();

	if (BoundGraph)
	{
		for (int32 i = 0; i < BoundGraph->Nodes.Num(); i++)
		{
			UBEBehaviorTreeDecoratorGraphNode_Decorator* Node = Cast<UBEBehaviorTreeDecoratorGraphNode_Decorator>(BoundGraph->Nodes[i]);
			if (Node)
			{
				Node->ResetNodeOwner();
			}
		}
	}
}

bool UBEBehaviorTreeGraphNode_CompositeDecorator::RefreshNodeClass()
{
	bool bUpdated = false;

	if (BoundGraph)
	{
		for (int32 i = 0; i < BoundGraph->Nodes.Num(); i++)
		{
			UBEBehaviorTreeDecoratorGraphNode_Decorator* Node = Cast<UBEBehaviorTreeDecoratorGraphNode_Decorator>(BoundGraph->Nodes[i]);
			if (Node)
			{
				const bool bNodeUpdated = Node->RefreshNodeClass();
				bUpdated = bUpdated || bNodeUpdated;
			}
		}
	}
	
	return bUpdated;
}

void UBEBehaviorTreeGraphNode_CompositeDecorator::UpdateNodeClassData()
{
	if (BoundGraph)
	{
		for (int32 i = 0; i < BoundGraph->Nodes.Num(); i++)
		{
			UBEBehaviorTreeDecoratorGraphNode_Decorator* Node = Cast<UBEBehaviorTreeDecoratorGraphNode_Decorator>(BoundGraph->Nodes[i]);
			if (Node)
			{
				Node->UpdateNodeClassData();
			}
		}
	}
}

void UBEBehaviorTreeGraphNode_CompositeDecorator::UpdateBrokenInstances()
{
	bHasBrokenInstances = false;
	if (BoundGraph)
	{
		for (int32 i = 0; i < BoundGraph->Nodes.Num(); i++)
		{
			UBEBehaviorTreeDecoratorGraphNode_Decorator* Node = Cast<UBEBehaviorTreeDecoratorGraphNode_Decorator>(BoundGraph->Nodes[i]);
			if (Node && Node->NodeInstance == nullptr)
			{
				bHasBrokenInstances = true;
				break;
			}
		}
	}
}

bool UBEBehaviorTreeGraphNode_CompositeDecorator::HasErrors() const
{
	return bHasObserverError || bHasBrokenInstances;
}

void UBEBehaviorTreeGraphNode_CompositeDecorator::CreateBoundGraph()
{
	// Create a new animation graph
	check(BoundGraph == NULL);

	// don't use white space in name here, it prevents links from being copied correctly
	BoundGraph = FBlueprintEditorUtils::CreateNewGraph(this, TEXT("CompositeDecorator"), UBEBehaviorTreeDecoratorGraph::StaticClass(), UEdBEGraphSchema_BehaviorTreeDecorator::StaticClass());
	check(BoundGraph);

	// Initialize the anim graph
	const UEdGraphSchema* Schema = BoundGraph->GetSchema();
	Schema->CreateDefaultNodesForGraph(*BoundGraph);

	// Add the new graph as a child of our parent graph
	GetGraph()->SubGraphs.Add(BoundGraph);
}

bool UBEBehaviorTreeGraphNode_CompositeDecorator::IsSubNode() const
{
	return true;
}

void UBEBehaviorTreeGraphNode_CompositeDecorator::CollectDecoratorData(TArray<UBTDecorator*>& NodeInstances, TArray<FBTDecoratorLogic>& Operations) const
{
	const UBEBehaviorTreeDecoratorGraph* MyGraph = Cast<const UBEBehaviorTreeDecoratorGraph>(BoundGraph);
	if (MyGraph)
	{
		MyGraph->CollectDecoratorData(NodeInstances, Operations);
	}
}

void UBEBehaviorTreeGraphNode_CompositeDecorator::SetDecoratorData(class UBTCompositeNode* InParentNode, uint8 InChildIndex)
{
	ParentNodeInstance = InParentNode;
	ChildIndex = InChildIndex;
}

void UBEBehaviorTreeGraphNode_CompositeDecorator::InitializeDecorator(class UBTDecorator* InnerDecorator)
{
	InnerDecorator->InitializeNode(ParentNodeInstance, 0, 0, 0);
	InnerDecorator->InitializeParentLink(ChildIndex);
}

void UBEBehaviorTreeGraphNode_CompositeDecorator::OnBlackboardUpdate()
{
	UBEBehaviorTreeDecoratorGraph* MyGraph = Cast<UBEBehaviorTreeDecoratorGraph>(BoundGraph);
	UBehaviorTree* BTAsset = Cast<UBehaviorTree>(GetOuter()->GetOuter());
	if (MyGraph && BTAsset)
	{
		for (int32 i = 0; i < MyGraph->Nodes.Num(); i++)
		{
			UBEBehaviorTreeDecoratorGraphNode_Decorator* MyNode = Cast<UBEBehaviorTreeDecoratorGraphNode_Decorator>(MyGraph->Nodes[i]);
			UBTNode* MyNodeInstance = MyNode ? Cast<UBTNode>(MyNode->NodeInstance) : NULL;
			if (MyNodeInstance)
			{
				MyNodeInstance->InitializeFromAsset(*BTAsset);
			}
		}
	}
}

void UBEBehaviorTreeGraphNode_CompositeDecorator::OnInnerGraphChanged()
{
	BuildDescription();

	bCanAbortFlow = false;

	UBEBehaviorTreeDecoratorGraph* MyGraph = Cast<UBEBehaviorTreeDecoratorGraph>(BoundGraph);
	if (MyGraph)
	{
		for (int32 i = 0; i < MyGraph->Nodes.Num(); i++)
		{
			UBEBehaviorTreeDecoratorGraphNode_Decorator* MyNode = Cast<UBEBehaviorTreeDecoratorGraphNode_Decorator>(MyGraph->Nodes[i]);
			UBTDecorator* MyNodeInstance = MyNode ? Cast<UBTDecorator>(MyNode->NodeInstance) : NULL;
			if (MyNodeInstance && MyNodeInstance->GetFlowAbortMode() != EBTFlowAbortMode::None)
			{
				bCanAbortFlow = true;
				break;
			}
		}
	}
}

int32 UBEBehaviorTreeGraphNode_CompositeDecorator::SpawnMissingNodes(const TArray<class UBTDecorator*>& NodeInstances, const TArray<struct FBTDecoratorLogic>& Operations, int32 StartIndex)
{
	int32 FirstIdxOutside = StartIndex + 1;
	
	UBEBehaviorTreeDecoratorGraph* MyGraph = Cast<UBEBehaviorTreeDecoratorGraph>(BoundGraph);
	if (MyGraph)
	{
		FirstIdxOutside = MyGraph->SpawnMissingNodes(NodeInstances, Operations, StartIndex);
	}

	return FirstIdxOutside;
}

void UBEBehaviorTreeGraphNode_CompositeDecorator::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property &&
		PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UBEBehaviorTreeGraphNode_CompositeDecorator, bShowOperations))
	{
		BuildDescription();
	}
}

struct FLogicDesc
{
	FString OperationDesc;
	int32 NumLeft;
};

void UpdateLogicOpStack(TArray<FLogicDesc>& OpStack, FString& Description, FString& Indent)
{
	if (OpStack.Num())
	{
		const int32 LastIdx = OpStack.Num() - 1;
		OpStack[LastIdx].NumLeft = OpStack[LastIdx].NumLeft - 1;

		if (OpStack[LastIdx].NumLeft <= 0)
		{
			OpStack.RemoveAt(LastIdx);
			Indent.LeftChopInline(2, false);

			UpdateLogicOpStack(OpStack, Description, Indent);
		}
		else
		{
			Description += Indent;
			Description += OpStack[LastIdx].OperationDesc;
		}
	}
}

void UBEBehaviorTreeGraphNode_CompositeDecorator::BuildDescription()
{
	FString BaseDesc("Composite Decorator");
	if (!bShowOperations)
	{
		CachedDescription = BaseDesc;
		return;
	}

	TArray<UBTDecorator*> NodeInstances;
	TArray<FBTDecoratorLogic> Operations;
	CollectDecoratorData(NodeInstances, Operations);

	TArray<FLogicDesc> OpStack;
	FString Description = BaseDesc + TEXT(":");
	FString Indent("\n");
	bool bPendingNotOp = false;

	for (int32 i = 0; i < Operations.Num(); i++)
	{
		const FBTDecoratorLogic& TestOp = Operations[i];
		if (TestOp.Operation == EBTDecoratorLogic::And ||
			TestOp.Operation == EBTDecoratorLogic::Or)
		{
			Indent += TEXT("- ");

			FLogicDesc NewOpDesc;
			NewOpDesc.NumLeft = TestOp.Number;
			NewOpDesc.OperationDesc = (TestOp.Operation == EBTDecoratorLogic::And) ? TEXT("AND") : TEXT("OR");
			
			OpStack.Add(NewOpDesc);
		}
		else if (TestOp.Operation == EBTDecoratorLogic::Not)
		{
			// special case: NOT before TEST
			if (Operations.IsValidIndex(i + 1) && Operations[i + 1].Operation == EBTDecoratorLogic::Test)
			{
				bPendingNotOp = true;
			}
			else
			{
				Indent += TEXT("- ");
				Description += Indent;
				Description += TEXT("NOT:");

				FLogicDesc NewOpDesc;
				NewOpDesc.NumLeft = 0;

				OpStack.Add(NewOpDesc);
			}
		}
		else if (TestOp.Operation == EBTDecoratorLogic::Test)
		{
			Description += Indent;
			if (bPendingNotOp)
			{
				Description += TEXT("NOT: ");
				bPendingNotOp = false;
			}

			Description += NodeInstances[TestOp.Number]->GetStaticDescription();
			UpdateLogicOpStack(OpStack, Description, Indent);
		}
	}

	CachedDescription = Description;
}

#undef LOCTEXT_NAMESPACE
