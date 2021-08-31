// Copyright 2021 RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "SGraphNode.h"

class UBEBehaviorTreeDecoratorGraphNode_Decorator;

class SGraphNode_Decorator : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SGraphNode_Decorator){}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UBEBehaviorTreeDecoratorGraphNode_Decorator* InNode);

	virtual FString GetNodeComment() const override;
};
