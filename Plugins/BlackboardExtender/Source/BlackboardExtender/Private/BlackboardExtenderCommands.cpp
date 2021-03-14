// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlackboardExtenderCommands.h"

#define LOCTEXT_NAMESPACE "FBlackboardExtenderModule"

void FBlackboardExtenderCommands::RegisterCommands()
{
	UI_COMMAND(BlackboardViewAction, "Blackboard View V2", "Open enhanced blackboard view", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(BlackboardDetailAction, "Blackboard Detail V2", "Open enhanced blackboard detail", EUserInterfaceActionType::Button, FInputGesture());
}

void FExtenderDebuggerCommands::RegisterCommands()
{
	UI_COMMAND(CurrentValues, "Current", "View current values", EUserInterfaceActionType::RadioButton, FInputChord());
	UI_COMMAND(SavedValues, "Saved", "View saved values", EUserInterfaceActionType::RadioButton, FInputChord());
}

#undef LOCTEXT_NAMESPACE
