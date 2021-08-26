// Copyright RadTuna. All Rights Reserved.

// Primary Include
#include "BlackboardConstantEditorCommands.h"


#define LOCTEXT_NAMESPACE "BlackboardConstantEditorCommands"

FBlackboardConstantEditorCommands::FBlackboardConstantEditorCommands()
	: TCommands<FBlackboardConstantEditorCommands>(TEXT("BlackboardConstantEditor"), LOCTEXT("ConstantEditor", "ConstantEditor"), NAME_None, FEditorStyle::GetStyleSetName())
{
}

void FBlackboardConstantEditorCommands::RegisterCommands()
{
	UI_COMMAND(RefreshConstantEditor, "Refresh", "Refresh constant keys.", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
