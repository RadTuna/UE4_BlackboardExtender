// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "BlackboardExtenderStyle.h"

class FBlackboardExtenderCommands : public TCommands<FBlackboardExtenderCommands>
{
public:

	FBlackboardExtenderCommands()
		: TCommands<FBlackboardExtenderCommands>(TEXT("BlackboardExtender"), NSLOCTEXT("Contexts", "BlackboardExtender", "BlackboardExtender Plugin"), NAME_None, FBlackboardExtenderStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> BlackboardViewAction;
	TSharedPtr<FUICommandInfo> BlackboardDetailAction;

};
