// Copyright Epic Games, Inc. All Rights Reserved.

#include "EdBEGraphSchema_BehaviorTree.h"
#include "Layout/SlateRect.h"
#include "EdGraphNode_Comment.h"
#include "Modules/ModuleManager.h"
#include "BlackboardExtenderEditorModule.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BTCompositeNode.h"
#include "BEBehaviorTreeEditorTypes.h"
#include "EdGraph/EdGraph.h"
#include "BEBehaviorTreeGraph.h"
#include "BEBehaviorTreeGraphNode.h"
#include "BEBehaviorTreeGraphNode_Composite.h"
#include "BEBehaviorTreeGraphNode_CompositeDecorator.h"
#include "BEBehaviorTreeGraphNode_Decorator.h"
#include "BEBehaviorTreeGraphNode_Root.h"
#include "BEBehaviorTreeGraphNode_Service.h"
#include "BEBehaviorTreeGraphNode_Task.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "ToolMenus.h"
#include "ObjectEditorUtils.h"
#include "IBEBehaviorTreeEditor.h"
#include "BehaviorTreeDebugger.h"
#include "GraphEditorActions.h"
#include "BehaviorTreeConnectionDrawingPolicy.h"
#include "Toolkits/ToolkitManager.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Tasks/BTTask_RunBehavior.h"
#include "BehaviorTree/Composites/BTComposite_SimpleParallel.h"
#include "BEBehaviorTreeGraphNode_SimpleParallel.h"
#include "BEBehaviorTreeGraphNode_SubtreeTask.h"

#define LOCTEXT_NAMESPACE "BehaviorTreeEditor"

int32 UEdBEGraphSchema_BehaviorTree::CurrentCacheRefreshID = 0;

//----------------------------------------------------------------------//
// 
//----------------------------------------------------------------------//
UEdGraphNode* FBEBehaviorTreeSchemaAction_AutoArrange::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
	UBEBehaviorTreeGraph* Graph = Cast<UBEBehaviorTreeGraph>(ParentGraph);
	if (Graph)
	{
		Graph->AutoArrange();
	}

	return NULL;
}

//----------------------------------------------------------------------//
// 
//----------------------------------------------------------------------//

UEdBEGraphSchema_BehaviorTree::UEdBEGraphSchema_BehaviorTree(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UEdBEGraphSchema_BehaviorTree::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	FGraphNodeCreator<UBEBehaviorTreeGraphNode_Root> NodeCreator(Graph);
	UBEBehaviorTreeGraphNode_Root* MyNode = NodeCreator.CreateNode();
	NodeCreator.Finalize();
	SetNodeMetaData(MyNode, FNodeMetadata::DefaultGraphNode);
}

void UEdBEGraphSchema_BehaviorTree::GetGraphNodeContextActions(FGraphContextMenuBuilder& ContextMenuBuilder, int32 SubNodeFlags) const
{
	Super::GetGraphNodeContextActions(ContextMenuBuilder, SubNodeFlags);

	if (SubNodeFlags == ESubNode::Decorator)
	{
		const FText Category = FObjectEditorUtils::GetCategoryText(UBEBehaviorTreeGraphNode_CompositeDecorator::StaticClass());
		UEdGraph* Graph = (UEdGraph*)ContextMenuBuilder.CurrentGraph;
		UBEBehaviorTreeGraphNode_CompositeDecorator* OpNode = NewObject<UBEBehaviorTreeGraphNode_CompositeDecorator>(Graph);
		TSharedPtr<FAISchemaAction_NewSubNode> AddOpAction = UAIGraphSchema::AddNewSubNodeAction(ContextMenuBuilder, Category, FText::FromString(OpNode->GetNodeTypeDescription()), FText::GetEmpty());
		AddOpAction->ParentNode = Cast<UBEBehaviorTreeGraphNode>(ContextMenuBuilder.SelectedObjects[0]);
		AddOpAction->NodeTemplate = OpNode;
	}
}

void UEdBEGraphSchema_BehaviorTree::GetSubNodeClasses(int32 SubNodeFlags, TArray<FGraphNodeClassData>& ClassData, UClass*& GraphNodeClass) const
{
	FBlackboardExtenderEditorModule& EditorModule = FModuleManager::GetModuleChecked<FBlackboardExtenderEditorModule>(TEXT("BehaviorTreeEditor"));
	FGraphNodeClassHelper* ClassCache = EditorModule.GetClassCache().Get();

	if (SubNodeFlags == ESubNode::Decorator)
	{
		ClassCache->GatherClasses(UBTDecorator::StaticClass(), ClassData);
		GraphNodeClass = UBEBehaviorTreeGraphNode_Decorator::StaticClass();
	}
	else
	{
		ClassCache->GatherClasses(UBTService::StaticClass(), ClassData);
		GraphNodeClass = UBEBehaviorTreeGraphNode_Service::StaticClass();
	}
}

void UEdBEGraphSchema_BehaviorTree::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	const FName PinCategory = ContextMenuBuilder.FromPin ?
		ContextMenuBuilder.FromPin->PinType.PinCategory : 
		UBEBehaviorTreeEditorTypes::PinCategory_MultipleNodes;

	const bool bNoParent = (ContextMenuBuilder.FromPin == NULL);
	const bool bOnlyTasks = (PinCategory == UBEBehaviorTreeEditorTypes::PinCategory_SingleTask);
	const bool bOnlyComposites = (PinCategory == UBEBehaviorTreeEditorTypes::PinCategory_SingleComposite);
	const bool bAllowComposites = bNoParent || !bOnlyTasks || bOnlyComposites;
	const bool bAllowTasks = bNoParent || !bOnlyComposites || bOnlyTasks;

	FBlackboardExtenderEditorModule& EditorModule = FModuleManager::GetModuleChecked<FBlackboardExtenderEditorModule>(TEXT("BehaviorTreeEditor"));
	FGraphNodeClassHelper* ClassCache = EditorModule.GetClassCache().Get();

	if (bAllowComposites)
	{
		FCategorizedGraphActionListBuilder CompositesBuilder(TEXT("Composites"));

		TArray<FGraphNodeClassData> NodeClasses;
		ClassCache->GatherClasses(UBTCompositeNode::StaticClass(), NodeClasses);

		const FString ParallelClassName = UBTComposite_SimpleParallel::StaticClass()->GetName();
		for (const auto& NodeClass : NodeClasses)
		{
			const FText NodeTypeName = FText::FromString(FName::NameToDisplayString(NodeClass.ToString(), false));

			TSharedPtr<FAISchemaAction_NewNode> AddOpAction = UAIGraphSchema::AddNewNodeAction(CompositesBuilder, NodeClass.GetCategory(), NodeTypeName, FText::GetEmpty());

			UClass* GraphNodeClass = UBEBehaviorTreeGraphNode_Composite::StaticClass();
			if (NodeClass.GetClassName() == ParallelClassName)
			{
				GraphNodeClass = UBEBehaviorTreeGraphNode_SimpleParallel::StaticClass();
			}

			UBEBehaviorTreeGraphNode* OpNode = NewObject<UBEBehaviorTreeGraphNode>(ContextMenuBuilder.OwnerOfTemporaries, GraphNodeClass);
			OpNode->ClassData = NodeClass;
			AddOpAction->NodeTemplate = OpNode;
		}

		ContextMenuBuilder.Append(CompositesBuilder);
	}

	if (bAllowTasks)
	{
		FCategorizedGraphActionListBuilder TasksBuilder(TEXT("Tasks"));

		TArray<FGraphNodeClassData> NodeClasses;
		ClassCache->GatherClasses(UBTTaskNode::StaticClass(), NodeClasses);

		for (const auto& NodeClass : NodeClasses)
		{
			const FText NodeTypeName = FText::FromString(FName::NameToDisplayString(NodeClass.ToString(), false));

			TSharedPtr<FAISchemaAction_NewNode> AddOpAction = UAIGraphSchema::AddNewNodeAction(TasksBuilder, NodeClass.GetCategory(), NodeTypeName, FText::GetEmpty());
			
			UClass* GraphNodeClass = UBEBehaviorTreeGraphNode_Task::StaticClass();
			if (NodeClass.GetClassName() == UBTTask_RunBehavior::StaticClass()->GetName())
			{
				GraphNodeClass = UBEBehaviorTreeGraphNode_SubtreeTask::StaticClass();
			}

			UBEBehaviorTreeGraphNode* OpNode = NewObject<UBEBehaviorTreeGraphNode>(ContextMenuBuilder.OwnerOfTemporaries, GraphNodeClass);
			OpNode->ClassData = NodeClass;
			AddOpAction->NodeTemplate = OpNode;
		}

		ContextMenuBuilder.Append(TasksBuilder);
	}
	
	if (bNoParent)
	{
		TSharedPtr<FBEBehaviorTreeSchemaAction_AutoArrange> Action = TSharedPtr<FBEBehaviorTreeSchemaAction_AutoArrange>(
			new FBEBehaviorTreeSchemaAction_AutoArrange(FText::GetEmpty(), LOCTEXT("AutoArrange", "Auto Arrange"), FText::GetEmpty(), 0)
			);

		ContextMenuBuilder.AddAction(Action);
	}
}

void UEdBEGraphSchema_BehaviorTree::GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	if (Context->Node && !Context->Pin)
	{
		const UBEBehaviorTreeGraphNode* BTGraphNode = Cast<const UBEBehaviorTreeGraphNode>(Context->Node);
		if (BTGraphNode && BTGraphNode->CanPlaceBreakpoints())
		{
			FToolMenuSection& Section = Menu->AddSection("EdGraphSchemaBreakpoints", LOCTEXT("BreakpointsHeader", "Breakpoints"));
			{
				Section.AddMenuEntry(FGraphEditorCommands::Get().ToggleBreakpoint);
				Section.AddMenuEntry(FGraphEditorCommands::Get().AddBreakpoint);
				Section.AddMenuEntry(FGraphEditorCommands::Get().RemoveBreakpoint);
				Section.AddMenuEntry(FGraphEditorCommands::Get().EnableBreakpoint);
				Section.AddMenuEntry(FGraphEditorCommands::Get().DisableBreakpoint);
			}
		}
	}

	Super::GetContextMenuActions(Menu, Context);
}

const FPinConnectionResponse UEdBEGraphSchema_BehaviorTree::CanCreateConnection(const UEdGraphPin* PinA, const UEdGraphPin* PinB) const
{
	// Make sure the pins are not on the same node
	if (PinA->GetOwningNode() == PinB->GetOwningNode())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinErrorSameNode","Both are on the same node"));
	}

	const bool bPinAIsSingleComposite = (PinA->PinType.PinCategory == UBEBehaviorTreeEditorTypes::PinCategory_SingleComposite);
	const bool bPinAIsSingleTask = (PinA->PinType.PinCategory == UBEBehaviorTreeEditorTypes::PinCategory_SingleTask);
	const bool bPinAIsSingleNode = (PinA->PinType.PinCategory == UBEBehaviorTreeEditorTypes::PinCategory_SingleNode);

	const bool bPinBIsSingleComposite = (PinB->PinType.PinCategory == UBEBehaviorTreeEditorTypes::PinCategory_SingleComposite);
	const bool bPinBIsSingleTask = (PinB->PinType.PinCategory == UBEBehaviorTreeEditorTypes::PinCategory_SingleTask);
	const bool bPinBIsSingleNode = (PinB->PinType.PinCategory == UBEBehaviorTreeEditorTypes::PinCategory_SingleNode);

	const bool bPinAIsTask = PinA->GetOwningNode()->IsA(UBEBehaviorTreeGraphNode_Task::StaticClass());
	const bool bPinAIsComposite = PinA->GetOwningNode()->IsA(UBEBehaviorTreeGraphNode_Composite::StaticClass());
	
	const bool bPinBIsTask = PinB->GetOwningNode()->IsA(UBEBehaviorTreeGraphNode_Task::StaticClass());
	const bool bPinBIsComposite = PinB->GetOwningNode()->IsA(UBEBehaviorTreeGraphNode_Composite::StaticClass());

	if ((bPinAIsSingleComposite && !bPinBIsComposite) || (bPinBIsSingleComposite && !bPinAIsComposite))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinErrorOnlyComposite","Only composite nodes are allowed"));
	}

	if ((bPinAIsSingleTask && !bPinBIsTask) || (bPinBIsSingleTask && !bPinAIsTask))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinErrorOnlyTask","Only task nodes are allowed"));
	}

	// Compare the directions
	if ((PinA->Direction == EGPD_Input) && (PinB->Direction == EGPD_Input))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinErrorInput", "Can't connect input node to input node"));
	}
	else if ((PinB->Direction == EGPD_Output) && (PinA->Direction == EGPD_Output))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinErrorOutput", "Can't connect output node to output node"));
	}

	class FNodeVisitorCycleChecker
	{
	public:
		/** Check whether a loop in the graph would be caused by linking the passed-in nodes */
		bool CheckForLoop(UEdGraphNode* StartNode, UEdGraphNode* EndNode)
		{
			VisitedNodes.Add(EndNode);
			return TraverseInputNodesToRoot(StartNode);
		}

	private:
		/** 
		 * Helper function for CheckForLoop()
		 * @param	Node	The node to start traversal at
		 * @return true if we reached a root node (i.e. a node with no input pins), false if we encounter a node we have already seen
		 */
		bool TraverseInputNodesToRoot(UEdGraphNode* Node)
		{
			VisitedNodes.Add(Node);

			// Follow every input pin until we cant any more ('root') or we reach a node we have seen (cycle)
			for (int32 PinIndex = 0; PinIndex < Node->Pins.Num(); ++PinIndex)
			{
				UEdGraphPin* MyPin = Node->Pins[PinIndex];

				if (MyPin->Direction == EGPD_Input)
				{
					for (int32 LinkedPinIndex = 0; LinkedPinIndex < MyPin->LinkedTo.Num(); ++LinkedPinIndex)
					{
						UEdGraphPin* OtherPin = MyPin->LinkedTo[LinkedPinIndex];
						if( OtherPin )
						{
							UEdGraphNode* OtherNode = OtherPin->GetOwningNode();
							if (VisitedNodes.Contains(OtherNode))
							{
								return false;
							}
							else
							{
								return TraverseInputNodesToRoot(OtherNode);
							}
						}
					}
				}
			}

			return true;
		}

		TSet<UEdGraphNode*> VisitedNodes;
	};

	// check for cycles
	FNodeVisitorCycleChecker CycleChecker;
	if(!CycleChecker.CheckForLoop(PinA->GetOwningNode(), PinB->GetOwningNode()))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinErrorcycle", "Can't create a graph cycle"));
	}

	const bool bPinASingleLink = bPinAIsSingleComposite || bPinAIsSingleTask || bPinAIsSingleNode;
	const bool bPinBSingleLink = bPinBIsSingleComposite || bPinBIsSingleTask || bPinBIsSingleNode;

	if (PinB->Direction == EGPD_Input && PinB->LinkedTo.Num() > 0)
	{
		if(bPinASingleLink)
		{
			return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_AB, LOCTEXT("PinConnectReplace", "Replace connection"));
		}
		else
		{
			return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_B, LOCTEXT("PinConnectReplace", "Replace connection"));
		}
	}
	else if (PinA->Direction == EGPD_Input && PinA->LinkedTo.Num() > 0)
	{
		if (bPinBSingleLink)
		{
			return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_AB, LOCTEXT("PinConnectReplace", "Replace connection"));
		}
		else
		{
			return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_A, LOCTEXT("PinConnectReplace", "Replace connection"));
		}
	}

	if (bPinASingleLink && PinA->LinkedTo.Num() > 0)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_A, LOCTEXT("PinConnectReplace", "Replace connection"));
	}
	else if(bPinBSingleLink && PinB->LinkedTo.Num() > 0)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_B, LOCTEXT("PinConnectReplace", "Replace connection"));
	}

	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, LOCTEXT("PinConnect", "Connect nodes"));
}

const FPinConnectionResponse UEdBEGraphSchema_BehaviorTree::CanMergeNodes(const UEdGraphNode* NodeA, const UEdGraphNode* NodeB) const
{
	// Make sure the nodes are not the same 
	if (NodeA == NodeB)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Both are the same node"));
	}

	const bool bNodeAIsDecorator = NodeA->IsA(UBEBehaviorTreeGraphNode_Decorator::StaticClass()) || NodeA->IsA(UBEBehaviorTreeGraphNode_CompositeDecorator::StaticClass());
	const bool bNodeAIsService = NodeA->IsA(UBEBehaviorTreeGraphNode_Service::StaticClass());
	const bool bNodeBIsComposite = NodeB->IsA(UBEBehaviorTreeGraphNode_Composite::StaticClass());
	const bool bNodeBIsTask = NodeB->IsA(UBEBehaviorTreeGraphNode_Task::StaticClass());
	const bool bNodeBIsDecorator = NodeB->IsA(UBEBehaviorTreeGraphNode_Decorator::StaticClass()) || NodeB->IsA(UBEBehaviorTreeGraphNode_CompositeDecorator::StaticClass());
	const bool bNodeBIsService = NodeB->IsA(UBEBehaviorTreeGraphNode_Service::StaticClass());

	if (FBehaviorTreeDebugger::IsPIENotSimulating())
	{
		if (bNodeAIsDecorator)
		{
			const UBEBehaviorTreeGraphNode* BTNodeA = Cast<const UBEBehaviorTreeGraphNode>(NodeA);
			const UBEBehaviorTreeGraphNode* BTNodeB = Cast<const UBEBehaviorTreeGraphNode>(NodeB);
			
			if (BTNodeA && BTNodeA->bInjectedNode)
			{
				return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("MergeInjectedNodeNoMove", "Can't move injected nodes!"));
			}

			if (BTNodeB && BTNodeB->bInjectedNode)
			{
				const UBEBehaviorTreeGraphNode* ParentNodeB = Cast<const UBEBehaviorTreeGraphNode>(BTNodeB->ParentNode);

				int32 FirstInjectedIdx = INDEX_NONE;
				for (int32 Idx = 0; Idx < ParentNodeB->Decorators.Num(); Idx++)
				{
					if (ParentNodeB->Decorators[Idx]->bInjectedNode)
					{
						FirstInjectedIdx = Idx;
						break;
					}
				}

				int32 NodeIdx = ParentNodeB->Decorators.IndexOfByKey(BTNodeB);
				if (NodeIdx != FirstInjectedIdx)
				{
					return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("MergeInjectedNodeAtEnd", "Decorators must be placed above injected nodes!"));
				}
			}

			if (BTNodeB && BTNodeB->Decorators.Num())
			{
				for (int32 Idx = 0; Idx < BTNodeB->Decorators.Num(); Idx++)
				{
					if (BTNodeB->Decorators[Idx]->bInjectedNode)
					{
						return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("MergeInjectedNodeAtEnd", "Decorators must be placed above injected nodes!"));
					}
				}
			}
		}

		if ((bNodeAIsDecorator && (bNodeBIsComposite || bNodeBIsTask || bNodeBIsDecorator))
			|| (bNodeAIsService && (bNodeBIsComposite || bNodeBIsTask || bNodeBIsService)))
		{
			return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT(""));
		}
	}

	return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT(""));
}

FLinearColor UEdBEGraphSchema_BehaviorTree::GetPinTypeColor(const FEdGraphPinType& PinType) const
{
	return FColor::White;
}

class FConnectionDrawingPolicy* UEdBEGraphSchema_BehaviorTree::CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const
{
	return new FBehaviorTreeConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements, InGraphObj);
}

bool UEdBEGraphSchema_BehaviorTree::IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const
{
	return CurrentCacheRefreshID != InVisualizationCacheID;
}

int32 UEdBEGraphSchema_BehaviorTree::GetCurrentVisualizationCacheID() const
{
	return CurrentCacheRefreshID;
}

void UEdBEGraphSchema_BehaviorTree::ForceVisualizationCacheClear() const
{
	++CurrentCacheRefreshID;
}

#undef LOCTEXT_NAMESPACE
