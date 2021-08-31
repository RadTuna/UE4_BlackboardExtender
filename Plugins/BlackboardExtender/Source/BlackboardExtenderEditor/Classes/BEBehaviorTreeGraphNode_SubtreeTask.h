// Copyright 2021 RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "BEBehaviorTreeGraphNode_Task.h"
#include "BEBehaviorTreeGraphNode_SubtreeTask.generated.h"

UCLASS()
class UBEBehaviorTreeGraphNode_SubtreeTask : public UBEBehaviorTreeGraphNode_Task
{
	GENERATED_UCLASS_BODY()

	/** UBehaviorTreeGraph.UpdateCounter value of subtree graph */
	int32 SubtreeVersion;

	/** path of behavior tree asset used to create injected nodes preview */
	FString SubtreePath;

	/** updates nodes injected from subtree's root */
	bool UpdateInjectedNodes();
};
