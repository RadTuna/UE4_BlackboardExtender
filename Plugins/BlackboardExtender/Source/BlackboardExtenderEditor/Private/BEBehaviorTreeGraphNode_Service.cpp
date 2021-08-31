// Copyright 2021 RadTuna. All Rights Reserved.

#include "BEBehaviorTreeGraphNode_Service.h"
#include "BehaviorTree/BTService.h"

UBEBehaviorTreeGraphNode_Service::UBEBehaviorTreeGraphNode_Service(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsSubNode = true;
}

void UBEBehaviorTreeGraphNode_Service::AllocateDefaultPins()
{
	//No Pins for services
}


FText UBEBehaviorTreeGraphNode_Service::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	const UBTService* Service = Cast<UBTService>(NodeInstance);
	if (Service != NULL)
	{
		return FText::FromString(Service->GetNodeName());
	}
	else if (!ClassData.GetClassName().IsEmpty())
	{
		FString StoredClassName = ClassData.GetClassName();
		StoredClassName.RemoveFromEnd(TEXT("_C"));

		return FText::Format(NSLOCTEXT("AIGraph", "NodeClassError", "Class {0} not found, make sure it's saved!"), FText::FromString(StoredClassName));
	}

	return Super::GetNodeTitle(TitleType);
}
