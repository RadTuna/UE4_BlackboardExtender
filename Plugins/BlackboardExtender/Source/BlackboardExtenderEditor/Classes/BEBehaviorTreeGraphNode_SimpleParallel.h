// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "BEBehaviorTreeGraphNode_Composite.h"
#include "BEBehaviorTreeGraphNode_SimpleParallel.generated.h"

class UEdGraphPin;

UCLASS()
class UBEBehaviorTreeGraphNode_SimpleParallel : public UBEBehaviorTreeGraphNode_Composite
{
	GENERATED_UCLASS_BODY()

	virtual void AllocateDefaultPins() override;
	virtual void GetPinHoverText(const UEdGraphPin& Pin, FString& HoverTextOut) const override;
};
