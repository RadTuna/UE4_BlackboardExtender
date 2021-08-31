// Copyright 2021 RadTuna. All Rights Reserved.

#include "BehaviorTreeEditorUtils.h"
#include "EdGraph/EdGraph.h"
#include "BehaviorTree/BTDecorator.h"
#include "BEBehaviorTreeDecoratorGraphNode_Decorator.h"
#include "BEBehaviorTreeGraphNode_Composite.h"
#include "BEBehaviorTreeGraphNode_CompositeDecorator.h"
#include "BEBehaviorTreeGraphNode_Decorator.h"
#include "BEBehaviorTreeGraphNode_Service.h"
#include "BEBehaviorTreeGraphNode_Task.h"

TArray<UObject*> BehaviorTreeEditorUtils::GetSelectionForPropertyEditor(const TSet<UObject*>& InSelection, FPropertySelectionInfo& OutSelectionInfo)
{
	TArray<UObject*> Selection;

	for (UObject* SelectionEntry : InSelection)
	{
		UBEBehaviorTreeGraphNode_Composite* GraphNode_Composite = Cast<UBEBehaviorTreeGraphNode_Composite>(SelectionEntry);
		if (GraphNode_Composite)
		{
			Selection.Add(GraphNode_Composite->NodeInstance);
			continue;
		}

		UBEBehaviorTreeGraphNode_Task* GraphNode_Task = Cast<UBEBehaviorTreeGraphNode_Task>(SelectionEntry);
		if (GraphNode_Task)
		{
			Selection.Add(GraphNode_Task->NodeInstance);
			continue;
		}

		UBEBehaviorTreeGraphNode_Decorator* GraphNode_Decorator1 = Cast<UBEBehaviorTreeGraphNode_Decorator>(SelectionEntry);
		if (GraphNode_Decorator1)
		{
			Selection.Add(GraphNode_Decorator1->NodeInstance);
			OutSelectionInfo.FoundDecorator = Cast<UBTDecorator>(GraphNode_Decorator1->NodeInstance);
			OutSelectionInfo.bInjectedNode = OutSelectionInfo.bInjectedNode || GraphNode_Decorator1->bInjectedNode;
			OutSelectionInfo.bRootLevelNode = GraphNode_Decorator1->bRootLevel;
			continue;
		}

		UBEBehaviorTreeDecoratorGraphNode_Decorator* GraphNode_Decorator2 = Cast<UBEBehaviorTreeDecoratorGraphNode_Decorator>(SelectionEntry);
		if (GraphNode_Decorator2)
		{
			Selection.Add(GraphNode_Decorator2->NodeInstance);
			OutSelectionInfo.bInjectedNode = OutSelectionInfo.bInjectedNode || !GraphNode_Decorator2->GetGraph()->bEditable;
			continue;
		}
			
		UBEBehaviorTreeGraphNode_Service* GraphNode_Service = Cast<UBEBehaviorTreeGraphNode_Service>(SelectionEntry);
		if (GraphNode_Service)
		{
			Selection.Add(GraphNode_Service->NodeInstance);
			continue;
		}

		UBEBehaviorTreeGraphNode_CompositeDecorator* GraphNode_CompDecorator = Cast<UBEBehaviorTreeGraphNode_CompositeDecorator>(SelectionEntry);
		if (GraphNode_CompDecorator)
		{
			OutSelectionInfo.FoundGraphNode_CompDecorator = GraphNode_CompDecorator;
			OutSelectionInfo.bInjectedNode = OutSelectionInfo.bInjectedNode || GraphNode_CompDecorator->bInjectedNode;
			OutSelectionInfo.bRootLevelNode = OutSelectionInfo.bRootLevelNode || GraphNode_CompDecorator->bRootLevel;
		}

		Selection.Add(SelectionEntry);
	}

	return Selection;
}
