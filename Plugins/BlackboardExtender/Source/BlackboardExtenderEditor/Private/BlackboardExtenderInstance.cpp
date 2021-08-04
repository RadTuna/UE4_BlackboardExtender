// Fill out your copyright notice in the Description page of Project Settings.

// Primary Include
#include "BlackboardExtenderInstance.h"

// Engine Include
#include "BlackboardExtenderCommands.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTreeEditor/Public/IBehaviorTreeEditor.h"

// User Include
#include "BlackboardDataV2.h"


FBlackboardExtenderInstance::FBlackboardExtenderInstance()
{
	ExtenderCommands = MakeShared<FUICommandList>();
}

FBlackboardExtenderInstance::~FBlackboardExtenderInstance()
{
}

void FBlackboardExtenderInstance::InitializeExtenderInstance(UObject* AssetData, TSharedRef<class IBehaviorTreeEditor> InBehaviorTreeEditor)
{
	UBlackboardDataV2* BlackboardDataToEdit = Cast<UBlackboardDataV2>(AssetData);
	if (BlackboardDataToEdit == nullptr)
	{
		return;
	}

	BlackboardData = BlackboardDataToEdit;
	BehaviorTreeEditor = InBehaviorTreeEditor;

	// Bind tab commands
	ExtenderCommands->MapAction(
		FBlackboardExtenderCommands::Get().BlackboardViewAction,
		FExecuteAction::CreateRaw(this, &FBlackboardExtenderInstance::OnOpenBlackboardView),
		FCanExecuteAction());

	ExtenderCommands->MapAction(
		FBlackboardExtenderCommands::Get().BlackboardDetailAction,
		FExecuteAction::CreateRaw(this, &FBlackboardExtenderInstance::OnOpenBlackboardDetailView),
		FCanExecuteAction());

	TSharedRef<FExtender> BlackboardExtender = MakeShared<FExtender>();
	BlackboardExtender->AddMenuExtension(
        "BlackboardEditor",
        EExtensionHook::After,
        ExtenderCommands,
        FMenuExtensionDelegate::CreateRaw(this, &FBlackboardExtenderInstance::CreateBlackboardMenu));

	BlackboardExtender->AddMenuExtension(
        "BehaviorTreeEditor",
        EExtensionHook::After,
        ExtenderCommands,
        FMenuExtensionDelegate::CreateRaw(this, &FBlackboardExtenderInstance::CreateBehaviorTreeMenu));
	
	BehaviorTreeEditor.Pin()->AddMenuExtender(BlackboardExtender);
	BehaviorTreeEditor.Pin()->RegenerateMenusAndToolbars();
}

void FBlackboardExtenderInstance::CreateBehaviorTreeMenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(FBlackboardExtenderCommands::Get().BlackboardViewAction);
}

void FBlackboardExtenderInstance::CreateBlackboardMenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(FBlackboardExtenderCommands::Get().BlackboardViewAction);
	MenuBuilder.AddMenuEntry(FBlackboardExtenderCommands::Get().BlackboardDetailAction);
}

void FBlackboardExtenderInstance::SpawnBlackboardView()
{
}

void FBlackboardExtenderInstance::SpawnBlackboardDetails()
{
}

void FBlackboardExtenderInstance::OnOpenBlackboardView()
{
	FText DialogText = FText::FromString(TEXT("Open Blackboard View!"));
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);

	SpawnBlackboardView();
}

void FBlackboardExtenderInstance::OnOpenBlackboardDetailView()
{
	FText DialogText = FText::FromString(TEXT("Open Blackboard Detail View!"));
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);

	SpawnBlackboardDetails();
}
