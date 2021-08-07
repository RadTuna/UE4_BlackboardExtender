// Copyright Epic Games, Inc. All Rights Reserved.

#include "EdBEGraphSchema_BehaviorTreeDecorator.h"
#include "Modules/ModuleManager.h"
#include "EdGraph/EdGraph.h"
#include "SoundClassGraph/SoundClassGraphSchema.h"
#include "BehaviorTree/BTDecorator.h"
#include "BlackboardExtenderEditor.h"
#include "BEBehaviorTreeDecoratorGraphNode.h"
#include "AIGraphTypes.h"
#include "BEBehaviorTreeDecoratorGraphNode_Decorator.h"
#include "BEBehaviorTreeDecoratorGraphNode_Logic.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "ToolMenus.h"
#include "GraphEditorSettings.h"
#include "GraphEditorActions.h"
#include "ScopedTransaction.h"
#include "Framework/Commands/GenericCommands.h"

#define LOCTEXT_NAMESPACE "BehaviorTreeDecoratorSchema"
#define SNAP_GRID (16) // @todo ensure this is the same as SNodePanel::GetSnapGridSize()

namespace DecoratorSchema
{
	// Maximum distance a drag can be off a node edge to require 'push off' from node
	const int32 NodeDistance = 60;
}

UEdGraphNode* FBEDecoratorSchemaAction_NewNode::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
	UEdGraphNode* ResultNode = NULL;

	// If there is a template, we actually use it
	if (NodeTemplate != NULL)
	{
		const FScopedTransaction Transaction(LOCTEXT("AddNode", "Add Node"));
		ParentGraph->Modify();
		if (FromPin)
		{
			FromPin->Modify();
		}

		NodeTemplate->SetFlags(RF_Transactional);

		// set outer to be the graph so it doesn't go away
		NodeTemplate->Rename(NULL, ParentGraph, REN_NonTransactional);

		ParentGraph->AddNode(NodeTemplate, true);

		NodeTemplate->CreateNewGuid();
		NodeTemplate->PostPlacedNewNode();
		NodeTemplate->AllocateDefaultPins();
		NodeTemplate->AutowireNewNode(FromPin);

		// For input pins, new node will generally overlap node being dragged off
		// Work out if we want to visually push away from connected node
		int32 XLocation = Location.X;
		if (FromPin && FromPin->Direction == EGPD_Input)
		{
			UEdGraphNode* PinNode = FromPin->GetOwningNode();
			const float XDelta = FMath::Abs(PinNode->NodePosX - Location.X);

			if (XDelta < DecoratorSchema::NodeDistance)
			{
				// Set location to edge of current node minus the max move distance
				// to force node to push off from connect node enough to give selection handle
				XLocation = PinNode->NodePosX - DecoratorSchema::NodeDistance;
			}
		}

		NodeTemplate->NodePosX = XLocation;
		NodeTemplate->NodePosY = Location.Y;
		NodeTemplate->SnapToGrid(SNAP_GRID);

		ResultNode = NodeTemplate;
	}

	return ResultNode;
}

UEdGraphNode* FBEDecoratorSchemaAction_NewNode::PerformAction(class UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2D Location, bool bSelectNewNode) 
{
	UEdGraphNode* ResultNode = NULL;
	if (FromPins.Num() > 0)
	{
		ResultNode = PerformAction(ParentGraph, FromPins[0], Location);

		// Try autowiring the rest of the pins
		for (int32 Index = 1; Index < FromPins.Num(); ++Index)
		{
			ResultNode->AutowireNewNode(FromPins[Index]);
		}
	}
	else
	{
		ResultNode = PerformAction(ParentGraph, NULL, Location, bSelectNewNode);
	}

	return ResultNode;
}

void FBEDecoratorSchemaAction_NewNode::AddReferencedObjects( FReferenceCollector& Collector )
{
	FEdGraphSchemaAction::AddReferencedObjects( Collector );

	// These don't get saved to disk, but we want to make sure the objects don't get GC'd while the action array is around
	Collector.AddReferencedObject( NodeTemplate );
}

//////////////////////////////////////////////////////////////////////////

UEdBEGraphSchema_BehaviorTreeDecorator::UEdBEGraphSchema_BehaviorTreeDecorator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PC_Boolean = TEXT("bool");
}

TSharedPtr<FBEDecoratorSchemaAction_NewNode> UEdBEGraphSchema_BehaviorTreeDecorator::AddNewDecoratorAction(FGraphContextMenuBuilder& ContextMenuBuilder, const FText& Category, const FText& MenuDesc, const FText& Tooltip)
{
	TSharedPtr<FBEDecoratorSchemaAction_NewNode> NewAction = TSharedPtr<FBEDecoratorSchemaAction_NewNode>(new FBEDecoratorSchemaAction_NewNode(Category, MenuDesc, Tooltip, 0));

	ContextMenuBuilder.AddAction( NewAction );

	return NewAction;
}

void UEdBEGraphSchema_BehaviorTreeDecorator::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	FGraphNodeCreator<UBEBehaviorTreeDecoratorGraphNode_Logic> NodeCreator(Graph);
	UBEBehaviorTreeDecoratorGraphNode_Logic* MyNode = NodeCreator.CreateNode();
	MyNode->LogicMode = EBEDecoratorLogicMode::Sink;
	SetNodeMetaData(MyNode, FNodeMetadata::DefaultGraphNode);
	NodeCreator.Finalize();
}

void UEdBEGraphSchema_BehaviorTreeDecorator::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	const UBEBehaviorTreeDecoratorGraphNode* ParentGraphNode = ContextMenuBuilder.FromPin 
		? Cast<UBEBehaviorTreeDecoratorGraphNode>(ContextMenuBuilder.FromPin->GetOuter()) : NULL;

	FBlackboardExtenderEditorModule& EditorModule = FModuleManager::GetModuleChecked<FBlackboardExtenderEditorModule>(TEXT("BehaviorTreeEditor"));
	FGraphNodeClassHelper* ClassCache = EditorModule.GetClassCache().Get();

	TArray<FGraphNodeClassData> NodeClasses;
	ClassCache->GatherClasses(UBTDecorator::StaticClass(), NodeClasses);

	for (const auto& NodeClass : NodeClasses)
	{
		const FText NodeTypeName = FText::FromString(NodeClass.ToString());
		TSharedPtr<FBEDecoratorSchemaAction_NewNode> AddOpAction = AddNewDecoratorAction(ContextMenuBuilder, NodeClass.GetCategory(), NodeTypeName, FText::GetEmpty());

		UBEBehaviorTreeDecoratorGraphNode_Decorator* OpNode = NewObject<UBEBehaviorTreeDecoratorGraphNode_Decorator>(ContextMenuBuilder.OwnerOfTemporaries);
		OpNode->ClassData = NodeClass;
		AddOpAction->NodeTemplate = OpNode;
	}

#if WITH_EDITOR
	UBEBehaviorTreeDecoratorGraphNode_Logic* LogicCDO = UBEBehaviorTreeDecoratorGraphNode_Logic::StaticClass()->GetDefaultObject<UBEBehaviorTreeDecoratorGraphNode_Logic>();
	LogicCDO->GetMenuEntries(ContextMenuBuilder);
#endif
}

void UEdBEGraphSchema_BehaviorTreeDecorator::GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	const UBEBehaviorTreeDecoratorGraphNode_Logic* LogicNode = Cast<const UBEBehaviorTreeDecoratorGraphNode_Logic>(Context->Node);
	if (Context->Graph && !Context->Graph->bEditable)
	{
		return;
	}

	if (Context->Pin)
	{
		// Only display the 'Break Links' option if there is a link to break!
		if (Context->Pin->LinkedTo.Num() > 0)
		{
			FToolMenuSection& Section = Menu->AddSection("DecoratorGraphSchemaPinActions", LOCTEXT("PinActionsMenuHeader", "Pin Actions"));
			Section.AddMenuEntry(FGraphEditorCommands::Get().BreakPinLinks);
		}
	}
	else if (Context->Node)
	{
		{
			FToolMenuSection& Section = Menu->AddSection("DecoratorGraphSchemaNodeActions", LOCTEXT("ClassActionsMenuHeader", "Node Actions"));
			Section.AddMenuEntry(FGraphEditorCommands::Get().AddExecutionPin);
			Section.AddMenuEntry(FGraphEditorCommands::Get().BreakNodeLinks);
			Section.AddMenuEntry(FGenericCommands::Get().Delete);
		}
	}
}

const FPinConnectionResponse UEdBEGraphSchema_BehaviorTreeDecorator::CanCreateConnection(const UEdGraphPin* PinA, const UEdGraphPin* PinB) const
{
	if (PinA == NULL || PinB == NULL)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("One of the Pins is NULL"));
	}

	// Make sure the pins are not on the same node
	if (PinA->GetOwningNode() == PinB->GetOwningNode())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Both are on the same node"));
	}

	// multiple links
	if (PinA->LinkedTo.Num() > 0 || PinB->LinkedTo.Num() > 0)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT(""));
	}

	// Compare the directions
	if (PinA->Direction == PinB->Direction)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT(""));
	}

	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT(""));
}

FLinearColor UEdBEGraphSchema_BehaviorTreeDecorator::GetPinTypeColor(const FEdGraphPinType& PinType) const
{
	return GetDefault<UGraphEditorSettings>()->BooleanPinTypeColor;
}

bool UEdBEGraphSchema_BehaviorTreeDecorator::ShouldHidePinDefaultValue(UEdGraphPin* Pin) const
{
	return true;
}

#undef LOCTEXT_NAMESPACE
