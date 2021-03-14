// Fill out your copyright notice in the Description page of Project Settings.

// Primary Include
#include "BlackboardExtender/Public/AssetTypeActions_ExtendBlackboard.h"

// Engine Include
#include "AIModule.h"
#include "BlackboardExtender.h"
#include "BlackboardExtenderInstance.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTreeEditor/Public/BehaviorTreeEditorModule.h"



FAssetTypeActions_ExtendBlackboard::FAssetTypeActions_ExtendBlackboard()
{
}

FAssetTypeActions_ExtendBlackboard::~FAssetTypeActions_ExtendBlackboard()
{
}

UClass* FAssetTypeActions_ExtendBlackboard::GetSupportedClass() const
{
	return UBlackboardData::StaticClass();
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

			FBlackboardExtenderModule& BlackboardExtenderModule = FModuleManager::GetModuleChecked<FBlackboardExtenderModule>("BlackboardExtender");
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
