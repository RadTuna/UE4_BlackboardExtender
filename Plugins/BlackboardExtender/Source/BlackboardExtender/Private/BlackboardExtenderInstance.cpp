// Fill out your copyright notice in the Description page of Project Settings.

// Primary Include
#include "BlackboardExtender/Public/BlackboardExtenderInstance.h"

// Engine Include
#include "BlackboardExtenderCommands.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTreeEditor/Public/IBehaviorTreeEditor.h"


FBlackboardExtenderInstance::FBlackboardExtenderInstance()
{
	ExtenderCommands = MakeShared<FUICommandList>();
}

FBlackboardExtenderInstance::~FBlackboardExtenderInstance()
{
}

void FBlackboardExtenderInstance::InitializeExtenderInstance(UObject* AssetData, TSharedRef<class IBehaviorTreeEditor> InBehaviorTreeEditor)
{
	UBehaviorTree* BehaviorTreeToEdit = Cast<UBehaviorTree>(AssetData);
	UBlackboardData* BlackboardDataToEdit = Cast<UBlackboardData>(AssetData);

	// Assignment behavior tree and blackboard
	if (BehaviorTreeToEdit != nullptr)
	{
		BehaviorTree = BehaviorTreeToEdit;
		if (BehaviorTreeToEdit->BlackboardAsset != nullptr)
		{
			BlackboardData = BehaviorTreeToEdit->BlackboardAsset;
		}
	}
	else if (BlackboardDataToEdit != nullptr)
	{
		BlackboardData = BlackboardDataToEdit;
	}
	else
	{
		checkNoEntry();
	}

	// Assignment behavior tree editor
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
	SNew()
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
