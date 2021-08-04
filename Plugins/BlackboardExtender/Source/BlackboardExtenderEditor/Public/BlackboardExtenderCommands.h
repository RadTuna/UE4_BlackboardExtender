// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "BlackboardExtenderStyle.h"

class FBlackboardExtenderCommands final : public TCommands<FBlackboardExtenderCommands>
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

class FExtenderDebuggerCommands final : public TCommands<FExtenderDebuggerCommands>
{
public:
	FExtenderDebuggerCommands()
		: TCommands<FExtenderDebuggerCommands>(TEXT("BlackboardExtender.Debugger"), NSLOCTEXT("Contexts", "Debugger", "Debugger"), NAME_None, FBlackboardExtenderStyle::GetStyleSetName())
	{
	}

	TSharedPtr<FUICommandInfo> CurrentValues;
	TSharedPtr<FUICommandInfo> SavedValues;

	/** Initialize commands */
	virtual void RegisterCommands() override;
};
