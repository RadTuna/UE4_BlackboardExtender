// Copyright 2021 RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "BEBehaviorTreeDecoratorGraphNode.h"
#include "AIGraphTypes.h"
#include "BEBehaviorTreeDecoratorGraphNode_Decorator.generated.h"

struct FGraphNodeClassData;

UCLASS()
class UBEBehaviorTreeDecoratorGraphNode_Decorator : public UBEBehaviorTreeDecoratorGraphNode 
{
	GENERATED_UCLASS_BODY()

	UPROPERTY()
	UObject* NodeInstance;

	UPROPERTY()
	FGraphNodeClassData ClassData;

	virtual void PostPlacedNewNode() override;
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	virtual EBTDecoratorLogic::Type GetOperationType() const override;

	virtual void PostEditImport() override;
	virtual void PostEditUndo() override;
	virtual void PrepareForCopying() override;
	void PostCopyNode();
	bool RefreshNodeClass();
	void UpdateNodeClassData();

protected:
	friend class UBEBehaviorTreeGraphNode_CompositeDecorator;
	virtual void ResetNodeOwner();
};
