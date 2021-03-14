// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


class BLACKBOARDEXTENDER_API FBlackboardExtenderInstance final
{
public:
	FBlackboardExtenderInstance();
	~FBlackboardExtenderInstance();

	void InitializeExtenderInstance(UObject* AssetData, TSharedRef<class IBehaviorTreeEditor> InBehaviorTreeEditor);

private:
	void CreateBehaviorTreeMenu(FMenuBuilder& MenuBuilder);
	void CreateBlackboardMenu(FMenuBuilder& MenuBuilder);
	
	void OnOpenBlackboardView();
	void OnOpenBlackboardDetailView();
	
private:
	// Current edited behavior tree
	class UBehaviorTree* BehaviorTree;
	
	// Current edited blackboard
	class UBlackboardData* BlackboardData;

	// Binded behavior tree editor
	TWeakPtr<class IBehaviorTreeEditor> BehaviorTreeEditor;

	TSharedPtr<FUICommandList> ExtenderCommands;
	
};
