// Copyright RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


class FBlackboardConstantEditorCommands : public TCommands<FBlackboardConstantEditorCommands>
{
public:
	FBlackboardConstantEditorCommands();

	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> RefreshConstantEditor;
	
};
