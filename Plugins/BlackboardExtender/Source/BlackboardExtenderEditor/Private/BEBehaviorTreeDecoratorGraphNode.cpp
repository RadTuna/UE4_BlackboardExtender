// Copyright 2021 RadTuna. All Rights Reserved.

#include "BEBehaviorTreeDecoratorGraphNode.h"
#include "BEBehaviorTreeDecoratorGraph.h"
#include "BEBehaviorTreeGraphNode_CompositeDecorator.h"
#include "EdBEGraphSchema_BehaviorTreeDecorator.h"

UBEBehaviorTreeDecoratorGraphNode::UBEBehaviorTreeDecoratorGraphNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bAllowModifingInputs = true;
}

UEdGraphPin* UBEBehaviorTreeDecoratorGraphNode::GetInputPin(int32 InputIndex) const
{
	check(InputIndex >= 0);

	for (int32 PinIndex = 0, FoundInputs = 0; PinIndex < Pins.Num(); PinIndex++)
	{
		if (Pins[PinIndex]->Direction == EGPD_Input)
		{
			if (InputIndex == FoundInputs)
			{
				return Pins[PinIndex];
			}
			else
			{
				FoundInputs++;
			}
		}
	}

	return NULL;
}

UEdGraphPin* UBEBehaviorTreeDecoratorGraphNode::GetOutputPin(int32 InputIndex) const
{
	check(InputIndex >= 0);

	for (int32 PinIndex = 0, FoundInputs = 0; PinIndex < Pins.Num(); PinIndex++)
	{
		if (Pins[PinIndex]->Direction == EGPD_Output)
		{
			if (InputIndex == FoundInputs)
			{
				return Pins[PinIndex];
			}
			else
			{
				FoundInputs++;
			}
		}
	}

	return NULL;
}

UBEBehaviorTreeDecoratorGraph* UBEBehaviorTreeDecoratorGraphNode::GetDecoratorGraph()
{
	return CastChecked<UBEBehaviorTreeDecoratorGraph>(GetGraph());
}

EBTDecoratorLogic::Type UBEBehaviorTreeDecoratorGraphNode::GetOperationType() const
{
	return EBTDecoratorLogic::Invalid;
}

bool UBEBehaviorTreeDecoratorGraphNode::CanUserDeleteNode() const
{
	const UBEBehaviorTreeDecoratorGraph* MyGraph = Cast<const UBEBehaviorTreeDecoratorGraph>(GetGraph());
	return MyGraph == NULL || MyGraph->bEditable;
}

void UBEBehaviorTreeDecoratorGraphNode::AutowireNewNode(UEdGraphPin* FromPin)
{
	Super::AutowireNewNode(FromPin);

	if (FromPin != NULL)
	{
		if (GetSchema()->TryCreateConnection(FromPin, FromPin->Direction == EGPD_Input ? GetOutputPin() : GetInputPin()))
		{
			FromPin->GetOwningNode()->NodeConnectionListChanged();
		}
	}
}

void UBEBehaviorTreeDecoratorGraphNode::NodeConnectionListChanged()
{
	Super::NodeConnectionListChanged();

	const UBEBehaviorTreeDecoratorGraph* MyGraph = CastChecked<UBEBehaviorTreeDecoratorGraph>(GetGraph());
	
	UBEBehaviorTreeGraphNode_CompositeDecorator* CompositeDecorator = Cast<UBEBehaviorTreeGraphNode_CompositeDecorator>(MyGraph->GetOuter());
	CompositeDecorator->OnInnerGraphChanged();
}

bool UBEBehaviorTreeDecoratorGraphNode::CanCreateUnderSpecifiedSchema(const UEdGraphSchema* DesiredSchema) const
{
	return DesiredSchema->GetClass()->IsChildOf(UEdBEGraphSchema_BehaviorTreeDecorator::StaticClass());
}

