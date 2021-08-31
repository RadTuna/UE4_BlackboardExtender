// Copyright 2021 RadTuna. All Rights Reserved.

// Primary Include
#include "AssetTypeActions_BlackboardConstant.h"

// Engine Include
#include "AIModule.h"

// User Include
#include "BlackboardConstant.h"
#include "BlackboardExtenderEditorModule.h"


FAssetTypeActions_BlackboardConstant::FAssetTypeActions_BlackboardConstant()
{
}

FAssetTypeActions_BlackboardConstant::~FAssetTypeActions_BlackboardConstant()
{
}

UClass* FAssetTypeActions_BlackboardConstant::GetSupportedClass() const
{
	return UBlackboardConstant::StaticClass();
}

void FAssetTypeActions_BlackboardConstant::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for(auto Object : InObjects)
	{
		UBlackboardConstant* BlackboardConstant = Cast<UBlackboardConstant>(Object);
		if(BlackboardConstant != nullptr)
		{
			FBlackboardExtenderEditorModule& BehaviorTreeEditorModule = FModuleManager::LoadModuleChecked<FBlackboardExtenderEditorModule>("BlackboardExtenderEditor");
			BehaviorTreeEditorModule.CreateBlackboardConstantEditor(EToolkitMode::Standalone, EditWithinLevelEditor, BlackboardConstant);
		}
	}
}

uint32 FAssetTypeActions_BlackboardConstant::GetCategories()
{
	IAIModule& AIModule = FModuleManager::LoadModuleChecked<IAIModule>("AIModule").Get();
	return AIModule.GetAIAssetCategoryBit();
}
