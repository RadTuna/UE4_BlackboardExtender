// Fill out your copyright notice in the Description page of Project Settings.

// Primary Include
#include "AssetTypeActions_ExtendBlackboard.h"

// Engine Include
#include "AIModule.h"
#include "BlackboardExtenderEditor.h"
#include "BlackboardExtenderInstance.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTreeEditor/Public/BehaviorTreeEditorModule.h"

// User Include
#include "BlackboardDataV2.h"


FAssetTypeActions_ExtendBlackboard::FAssetTypeActions_ExtendBlackboard()
{
}

FAssetTypeActions_ExtendBlackboard::~FAssetTypeActions_ExtendBlackboard()
{
}

UClass* FAssetTypeActions_ExtendBlackboard::GetSupportedClass() const
{
	return UBlackboardDataV2::StaticClass();
}

void FAssetTypeActions_ExtendBlackboard::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto Object : InObjects)
	{
		auto* BlackboardData = Cast<UBlackboardData>(Object);
		if (BlackboardData != nullptr)
		{	
			FBehaviorTreeEditorModule& BehaviorTreeEditorModule = FModuleManager::LoadModuleChecked<FBehaviorTreeEditorModule>("BehaviorTreeEditor");
			TSharedRef<IBehaviorTreeEditor> NewEditor = BehaviorTreeEditorModule.CreateBehaviorTreeEditor(EToolkitMode::Standalone, EditWithinLevelEditor, BlackboardData);

			FBlackboardExtenderEditorModule& BlackboardExtenderModule = FModuleManager::GetModuleChecked<FBlackboardExtenderEditorModule>("BlackboardExtenderEditor");
			TSharedPtr<FBlackboardExtenderInstance> BlackboardExtenderInstance = BlackboardExtenderModule.GetBlackboardExtenderInstance();

			BlackboardExtenderInstance->InitializeExtenderInstance(Object, NewEditor);
		}
	}
}

uint32 FAssetTypeActions_ExtendBlackboard::GetCategories()
{
	IAIModule& AIModule = FModuleManager::LoadModuleChecked<IAIModule>("AIModule").Get();
	return AIModule.GetAIAssetCategoryBit();
}
