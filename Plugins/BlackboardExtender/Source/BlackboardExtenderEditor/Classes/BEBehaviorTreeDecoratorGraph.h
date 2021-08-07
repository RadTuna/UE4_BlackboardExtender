// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EdGraph/EdGraph.h"
#include "BEBehaviorTreeDecoratorGraph.generated.h"

class UBEBehaviorTreeDecoratorGraphNode;
class UEdGraphPin;

UCLASS()
class UBEBehaviorTreeDecoratorGraph : public UEdGraph
{
	GENERATED_UCLASS_BODY()

	void CollectDecoratorData(TArray<class UBTDecorator*>& DecoratorInstances, TArray<struct FBTDecoratorLogic>& DecoratorOperations) const;
	int32 SpawnMissingNodes(const TArray<class UBTDecorator*>& NodeInstances, const TArray<struct FBTDecoratorLogic>& Operations, int32 StartIndex);

protected:

	const class UBEBehaviorTreeDecoratorGraphNode* FindRootNode() const;
	void CollectDecoratorDataWorker(const class UBEBehaviorTreeDecoratorGraphNode* Node, TArray<class UBTDecorator*>& DecoratorInstances, TArray<struct FBTDecoratorLogic>& DecoratorOperations) const;

	UEdGraphPin* FindFreePin(UEdGraphNode* Node, EEdGraphPinDirection Direction);
	UBEBehaviorTreeDecoratorGraphNode* SpawnMissingNodeWorker(const TArray<class UBTDecorator*>& NodeInstances, const TArray<struct FBTDecoratorLogic>& Operations, int32& Index,
		UEdGraphNode* ParentGraphNode, int32 ChildIdx);

};
