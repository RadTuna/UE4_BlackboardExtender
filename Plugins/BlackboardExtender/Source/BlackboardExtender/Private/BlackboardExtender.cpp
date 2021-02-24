// Copyright Epic Games, Inc. All Rights Reserved.

// Primary Include
#include "BlackboardExtender.h"

// Engine Include
#include "BehaviorTreeEditor/Public/BehaviorTreeEditorModule.h"
#include "Misc/MessageDialog.h"

// User Include
#include "BlackboardExtenderStyle.h"
#include "BlackboardExtenderCommands.h"


static const FName BlackboardExtenderTabName("BlackboardExtender");

#define LOCTEXT_NAMESPACE "FBlackboardExtenderModule"

void FBlackboardExtenderModule::StartupModule()
{
	FBlackboardExtenderStyle::Initialize();
	FBlackboardExtenderStyle::ReloadTextures();

	FBlackboardExtenderCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	// bind blackboard view command and action(function)
	PluginCommands->MapAction(
		FBlackboardExtenderCommands::Get().BlackboardViewAction,
		FExecuteAction::CreateRaw(this, &FBlackboardExtenderModule::PluginButtonClicked),
		FCanExecuteAction());

	// bind blackboard detail command and action(function)
	PluginCommands->MapAction(
	    FBlackboardExtenderCommands::Get().BlackboardDetailAction,
		FExecuteAction::CreateRaw(this, &FBlackboardExtenderModule::PluginButtonClicked),
		FCanExecuteAction());

	FBehaviorTreeEditorModule& BehaviorTreeEditorModule = FModuleManager::LoadModuleChecked<FBehaviorTreeEditorModule>("BehaviorTreeEditor");

	TSharedRef<FExtender> BlackboardExtender = MakeShared<FExtender>();
	BlackboardExtender->AddMenuExtension(
		"BlackboardEditor",
		EExtensionHook::After,
		PluginCommands,
		FMenuExtensionDelegate::CreateRaw(this, &FBlackboardExtenderModule::CreateBlackboardMenu));

	BlackboardExtender->AddMenuExtension(
		"BehaviorTreeEditor",
		EExtensionHook::After,
		PluginCommands,
		FMenuExtensionDelegate::CreateRaw(this, &FBlackboardExtenderModule::CreateBehaviorTreeMenu));

	BehaviorTreeEditorModule.GetMenuExtensibilityManager()->AddExtender(BlackboardExtender);

}

void FBlackboardExtenderModule::ShutdownModule()
{
	FBlackboardExtenderStyle::Shutdown();
	FBlackboardExtenderCommands::Unregister();
}

void FBlackboardExtenderModule::PluginButtonClicked()
{
	FText DialogText = FText::FromString(TEXT("Test Out"));
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FBlackboardExtenderModule::CreateBlackboardMenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(FBlackboardExtenderCommands::Get().BlackboardViewAction);
	MenuBuilder.AddMenuEntry(FBlackboardExtenderCommands::Get().BlackboardDetailAction);
}

void FBlackboardExtenderModule::CreateBehaviorTreeMenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(FBlackboardExtenderCommands::Get().BlackboardViewAction);
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBlackboardExtenderModule, BlackboardExtender)
