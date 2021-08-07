// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "BEBehaviorTreeDecoratorGraphNode.h"
#include "BEBehaviorTreeDecoratorGraphNode_Logic.generated.h"

UENUM()
namespace EBEDecoratorLogicMode
{
	enum Type
	{
		Sink,
		And,
		Or,
		Not,
	};
}

UCLASS()
class UBEBehaviorTreeDecoratorGraphNode_Logic : public UBEBehaviorTreeDecoratorGraphNode
{
	GENERATED_UCLASS_BODY()

	UPROPERTY()
	TEnumAsByte<EBEDecoratorLogicMode::Type> LogicMode;

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void AllocateDefaultPins() override;
	virtual bool CanUserDeleteNode() const override;
	virtual EBTDecoratorLogic::Type GetOperationType() const override;

	virtual void GetMenuEntries(struct FGraphContextMenuBuilder& ContextMenuBuilder) const override;

	bool CanRemovePins() const;
	bool CanAddPins() const;

	UEdGraphPin* AddInputPin();
	void RemoveInputPin(class UEdGraphPin* Pin);

	EBEDecoratorLogicMode::Type GetLogicMode(EBTDecoratorLogic::Type Op) const;
};
