// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "BEBehaviorTreeGraphNode.h"
#include "BEBehaviorTreeGraphNode_Decorator.generated.h"

UCLASS()
class UBEBehaviorTreeGraphNode_Decorator : public UBEBehaviorTreeGraphNode
{
	GENERATED_UCLASS_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void AllocateDefaultPins() override;
	void CollectDecoratorData(TArray<class UBTDecorator*>& NodeInstances, TArray<struct FBTDecoratorLogic>& Operations) const;
};
