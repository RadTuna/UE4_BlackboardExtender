// Copyright 2021 RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class UBEBehaviorTreeGraphNode_CompositeDecorator;
class UBTDecorator;

namespace BehaviorTreeEditorUtils
{
	struct FPropertySelectionInfo
	{
		FPropertySelectionInfo()
			: FoundGraphNode_CompDecorator(nullptr)
			, FoundDecorator(nullptr)
			, bInjectedNode(false)
			, bRootLevelNode(false)
		{
		}

		UBEBehaviorTreeGraphNode_CompositeDecorator* FoundGraphNode_CompDecorator;
		UBTDecorator* FoundDecorator;
		bool bInjectedNode;
		bool bRootLevelNode;
	};

	/** Given a selection of nodes, return the instances that should be selected be selected for editing in the property panel */
	TArray<UObject*> GetSelectionForPropertyEditor(const TSet<UObject*>& InSelection, FPropertySelectionInfo& OutSelectionInfo);
}
