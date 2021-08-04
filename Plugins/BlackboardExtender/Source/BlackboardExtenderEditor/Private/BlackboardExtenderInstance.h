// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


class BLACKBOARDEXTENDEREDITOR_API FBlackboardExtenderInstance final
{
public:
	FBlackboardExtenderInstance();
	~FBlackboardExtenderInstance();

	void InitializeExtenderInstance(UObject* AssetData, TSharedRef<class IBehaviorTreeEditor> InBehaviorTreeEditor);

private:
	void CreateBehaviorTreeMenu(FMenuBuilder& MenuBuilder);
	void CreateBlackboardMenu(FMenuBuilder& MenuBuilder);

	void SpawnBlackboardView();
	void SpawnBlackboardDetails();
	
	void OnOpenBlackboardView();
	void OnOpenBlackboardDetailView();
	
private:
	// Current edited blackboard
	class UBlackboardDataV2* BlackboardData;

	// Binded behavior tree editor
	TWeakPtr<class IBehaviorTreeEditor> BehaviorTreeEditor;

	TSharedPtr<FUICommandList> ExtenderCommands;
	
};
