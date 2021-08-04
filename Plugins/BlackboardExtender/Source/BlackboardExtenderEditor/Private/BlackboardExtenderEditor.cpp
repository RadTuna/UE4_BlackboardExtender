// Copyright Epic Games, Inc. All Rights Reserved.

// Primary Include
#include "BlackboardExtenderEditor.h"

// User Include
#include "AssetToolsModule.h"
#include "AssetTypeAction/AssetTypeActions_ExtendBehaviorTree.h"
#include "AssetTypeAction/AssetTypeActions_ExtendBlackboard.h"
#include "BlackboardExtenderStyle.h"
#include "BlackboardExtenderCommands.h"
#include "BlackboardExtenderInstance.h"
#include "IAssetTools.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"


#define LOCTEXT_NAMESPACE "FBlackboardExtenderEditorModule"

void FBlackboardExtenderEditorModule::StartupModule()
{
	// Initialize UI style
	FBlackboardExtenderStyle::Initialize();
	FBlackboardExtenderStyle::ReloadTextures();

	// Register commands
	FBlackboardExtenderCommands::Register();
	FExtenderDebuggerCommands::Register();

	// Make extender instance
	BlackboardExtenderInstance = MakeShared<FBlackboardExtenderInstance>();

	// Unregister asset type actions in behavior tree editor
	IAssetTools& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	TWeakPtr<IAssetTypeActions> OldBehaviorTreeAssetTypeActions = AssetToolsModule.GetAssetTypeActionsForClass(UBehaviorTree::StaticClass());
	AssetToolsModule.UnregisterAssetTypeActions(OldBehaviorTreeAssetTypeActions.Pin().ToSharedRef());

	//TWeakPtr<IAssetTypeActions> OldBlackboardAssetTypeActions = AssetToolsModule.GetAssetTypeActionsForClass(UBlackboardData::StaticClass());
	//AssetToolsModule.UnregisterAssetTypeActions(OldBlackboardAssetTypeActions.Pin().ToSharedRef());
	
	// Register asset type actions
	TSharedPtr<FAssetTypeActions_ExtendBehaviorTree> BehaviorTreeAssetTypeActions = MakeShared<FAssetTypeActions_ExtendBehaviorTree>();
	AssetTypeActionsList.Add(BehaviorTreeAssetTypeActions);
	AssetToolsModule.RegisterAssetTypeActions(BehaviorTreeAssetTypeActions.ToSharedRef());

	TSharedPtr<FAssetTypeActions_ExtendBlackboard> BlackboardAssetTypeActions = MakeShared<FAssetTypeActions_ExtendBlackboard>();
	AssetTypeActionsList.Add(BlackboardAssetTypeActions);
	AssetToolsModule.RegisterAssetTypeActions(BlackboardAssetTypeActions.ToSharedRef());
}

void FBlackboardExtenderEditorModule::ShutdownModule()
{
	FBlackboardExtenderStyle::Shutdown();

	// Unregister commands
	FBlackboardExtenderCommands::Unregister();
	FExtenderDebuggerCommands::Unregister();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBlackboardExtenderEditorModule, BlackboardExtenderEditor)