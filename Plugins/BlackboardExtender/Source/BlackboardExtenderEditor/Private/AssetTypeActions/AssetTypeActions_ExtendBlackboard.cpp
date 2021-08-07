// Fill out your copyright notice in the Description page of Project Settings.

// Primary Include
#include "AssetTypeActions_ExtendBlackboard.h"

// Engine Include
#include "AIModule.h"
#include "BlackboardExtenderEditor.h"
#include "BehaviorTreeEditor/Public/BehaviorTreeEditorModule.h"

// User Include
#include "BEBlackboardData.h"


FAssetTypeActions_ExtendBlackboard::FAssetTypeActions_ExtendBlackboard()
{
}

FAssetTypeActions_ExtendBlackboard::~FAssetTypeActions_ExtendBlackboard()
{
}

UClass* FAssetTypeActions_ExtendBlackboard::GetSupportedClass() const
{
	return UBEBlackboardData::StaticClass();
}

void FAssetTypeActions_ExtendBlackboard::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for(auto Object : InObjects)
	{
		auto BlackboardData = Cast<UBlackboardData>(Object);
		if(BlackboardData != nullptr)
		{
			FBlackboardExtenderEditorModule& BehaviorTreeEditorModule = FModuleManager::LoadModuleChecked<FBlackboardExtenderEditorModule>("BlackboardExtenderEditor");
			BehaviorTreeEditorModule.CreateBehaviorTreeEditor(EToolkitMode::Standalone, EditWithinLevelEditor, BlackboardData);
		}
	}
}

uint32 FAssetTypeActions_ExtendBlackboard::GetCategories()
{
	IAIModule& AIModule = FModuleManager::LoadModuleChecked<IAIModule>("AIModule").Get();
	return AIModule.GetAIAssetCategoryBit();
}
