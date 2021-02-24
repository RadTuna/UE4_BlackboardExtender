// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlackboardExtenderCommands.h"

#define LOCTEXT_NAMESPACE "FBlackboardExtenderModule"

void FBlackboardExtenderCommands::RegisterCommands()
{
	UI_COMMAND(BlackboardViewAction, "Blackboard View V2", "Open enhanced blackboard view", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(BlackboardDetailAction, "Blackboard Detail V2", "Open enhanced blackboard detail", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
