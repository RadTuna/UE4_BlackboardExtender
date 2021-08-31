// Copyright 2021 RadTuna. All Rights Reserved.

#include "BEBehaviorTreeGraphNode_Decorator.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/BTCompositeNode.h"

UBEBehaviorTreeGraphNode_Decorator::UBEBehaviorTreeGraphNode_Decorator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsSubNode = true;
}

void UBEBehaviorTreeGraphNode_Decorator::AllocateDefaultPins()
{
	//No Pins for decorators
}

FText UBEBehaviorTreeGraphNode_Decorator::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	const UBTDecorator* Decorator = Cast<UBTDecorator>(NodeInstance);
	if (Decorator != NULL)
	{
		return FText::FromString(Decorator->GetNodeName());
	}
	else if (!ClassData.GetClassName().IsEmpty())
	{
		FString StoredClassName = ClassData.GetClassName();
		StoredClassName.RemoveFromEnd(TEXT("_C"));

		return FText::Format(NSLOCTEXT("AIGraph", "NodeClassError", "Class {0} not found, make sure it's saved!"), FText::FromString(StoredClassName));
	}

	return Super::GetNodeTitle(TitleType);
}

void UBEBehaviorTreeGraphNode_Decorator::CollectDecoratorData(TArray<UBTDecorator*>& NodeInstances, TArray<FBTDecoratorLogic>& Operations) const
{
	if (NodeInstance)
	{
		UBTDecorator* DecoratorNode = (UBTDecorator*)NodeInstance;
		const int32 InstanceIdx = NodeInstances.Add(DecoratorNode);
		Operations.Add(FBTDecoratorLogic(EBTDecoratorLogic::Test, InstanceIdx));
	}
}
