// Copyright RadTuna. All Rights Reserved.

// Primary Include
#include "BlackboardConstantEditorCommands.h"

// User Include
#include "BlackboardConstantEditor.h"


#define LOCTEXT_NAMESPACE "BlackboardConstantEditorCommands"

FBlackboardConstantEditorCommands::FBlackboardConstantEditorCommands()
	: TCommands<FBlackboardConstantEditorCommands>(TEXT("BlackboardConstant"), LOCTEXT("ConstantEditor", "ConstantEditor"), NAME_None, FBlackboardConstantStyle::GetStyleName())
{
}

void FBlackboardConstantEditorCommands::RegisterCommands()
{
	UI_COMMAND(RefreshConstantEditor, "Refresh", "Refresh constant keys.", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
