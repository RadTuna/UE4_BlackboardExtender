// Copyright Epic Games, Inc. All Rights Reserved.

#include "BEBehaviorTreeDecoratorGraphNode_Logic.h"
#include "EdGraph/EdGraph.h"
#include "EdBEGraphSchema_BehaviorTreeDecorator.h"

UBEBehaviorTreeDecoratorGraphNode_Logic::UBEBehaviorTreeDecoratorGraphNode_Logic(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

bool UBEBehaviorTreeDecoratorGraphNode_Logic::CanUserDeleteNode() const
{
	return LogicMode != EBEDecoratorLogicMode::Sink;
}

void UBEBehaviorTreeDecoratorGraphNode_Logic::AllocateDefaultPins()
{
	AddInputPin();
	if (LogicMode == EBEDecoratorLogicMode::And || LogicMode == EBEDecoratorLogicMode::Or)
	{
		AddInputPin();
	}

	if (LogicMode != EBEDecoratorLogicMode::Sink)
	{
		CreatePin(EGPD_Output, TEXT("Transition"), TEXT("Out"));
	}
}

static FString DescribeLogicModeHelper(const EBEDecoratorLogicMode::Type& Mode)
{
	FString Desc[] = { TEXT("Result"), TEXT("AND"), TEXT("OR"), TEXT("NOT") };
	return Desc[Mode];
}

FText UBEBehaviorTreeDecoratorGraphNode_Logic::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(DescribeLogicModeHelper(LogicMode));
}

void UBEBehaviorTreeDecoratorGraphNode_Logic::GetMenuEntries(struct FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	EBEDecoratorLogicMode::Type Modes[] = { EBEDecoratorLogicMode::And, EBEDecoratorLogicMode::Or, EBEDecoratorLogicMode::Not };
	const int32 NumModes = sizeof(Modes) / sizeof(Modes[0]);
	for (int32 i = 0; i < NumModes; i++)
	{
		TSharedPtr<FBEDecoratorSchemaAction_NewNode> AddOpAction = UEdBEGraphSchema_BehaviorTreeDecorator::AddNewDecoratorAction(ContextMenuBuilder, NSLOCTEXT("BehaviorTreeGraphNode_Logic", "Logic", "Logic"), FText::FromString(DescribeLogicModeHelper(Modes[i])), FText::GetEmpty());

		UBEBehaviorTreeDecoratorGraphNode_Logic* OpNode = NewObject<UBEBehaviorTreeDecoratorGraphNode_Logic>(ContextMenuBuilder.OwnerOfTemporaries);
		OpNode->LogicMode = Modes[i];
		AddOpAction->NodeTemplate = OpNode;
	}
}

bool UBEBehaviorTreeDecoratorGraphNode_Logic::CanAddPins() const
{
	return (LogicMode == EBEDecoratorLogicMode::And || LogicMode == EBEDecoratorLogicMode::Or);
}

bool UBEBehaviorTreeDecoratorGraphNode_Logic::CanRemovePins() const
{
	int32 NumInputLinks = 0;
	for (int32 i = 0; i < Pins.Num(); i++)
	{
		if (Pins[i]->Direction == EGPD_Input)
		{
			NumInputLinks++;
		}
	}

	return (NumInputLinks > 2) && CanAddPins();
}

UEdGraphPin* UBEBehaviorTreeDecoratorGraphNode_Logic::AddInputPin()
{
	return CreatePin(EGPD_Input, TEXT("Transition"), TEXT("In"));
}

void UBEBehaviorTreeDecoratorGraphNode_Logic::RemoveInputPin(class UEdGraphPin* Pin)
{
	Pin->MarkPendingKill();
	Pins.Remove(Pin);
}

EBTDecoratorLogic::Type UBEBehaviorTreeDecoratorGraphNode_Logic::GetOperationType() const
{
	EBTDecoratorLogic::Type LogicTypes[] = { EBTDecoratorLogic::Invalid, EBTDecoratorLogic::And, EBTDecoratorLogic::Or, EBTDecoratorLogic::Not };
	return LogicTypes[LogicMode];
}

EBEDecoratorLogicMode::Type UBEBehaviorTreeDecoratorGraphNode_Logic::GetLogicMode(EBTDecoratorLogic::Type Op) const
{
	EBEDecoratorLogicMode::Type LogicTypes[] = { EBEDecoratorLogicMode::Sink, EBEDecoratorLogicMode::Sink, EBEDecoratorLogicMode::And, EBEDecoratorLogicMode::Or, EBEDecoratorLogicMode::Not };
	return LogicTypes[Op];
}
