// Fill out your copyright notice in the Description page of Project Settings.

// Primary Include
#include "AssetTypeActions_ExtendBehaviorTree.h"

// Engine Include
#include "AIModule.h"
#include "BehaviorTreeEditorModule.h"
#include "BlackboardDataV2.h"
#include "BlackboardExtenderEditor.h"
#include "BlackboardExtenderInstance.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"


#define LOCTEXT_NAMESPACE "AssetTypeActions"

FAssetTypeActions_ExtendBehaviorTree::FAssetTypeActions_ExtendBehaviorTree()
{
}

FAssetTypeActions_ExtendBehaviorTree::~FAssetTypeActions_ExtendBehaviorTree()
{
}


UClass* FAssetTypeActions_ExtendBehaviorTree::GetSupportedClass() const
{
	return UBehaviorTree::StaticClass();
}

void FAssetTypeActions_ExtendBehaviorTree::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools"));
	
	for (UObject* Object : InObjects)
	{
		auto* BehaviorTree = Cast<UBehaviorTree>(Object);
		if (BehaviorTree != nullptr)
		{
			FBehaviorTreeEditorModule& BehaviorTreeEditorModule = FModuleManager::GetModuleChecked<FBehaviorTreeEditorModule>("BehaviorTreeEditor");
			TSharedRef<IBehaviorTreeEditor> NewEditor = BehaviorTreeEditorModule.CreateBehaviorTreeEditor(Mode, EditWithinLevelEditor, BehaviorTree);
			
			FBlackboardExtenderEditorModule& BlackboardExtenderModule = FModuleManager::GetModuleChecked<FBlackboardExtenderEditorModule>("BlackboardExtenderEditor");
			TSharedPtr<FBlackboardExtenderInstance> BlackboardExtenderInstance = BlackboardExtenderModule.GetBlackboardExtenderInstance();

			BlackboardExtenderInstance->InitializeExtenderInstance(Object, NewEditor);

			TArray<TWeakPtr<IAssetTypeActions>> AssetTypeActionsList = AssetToolsModule.Get().GetAssetTypeActionsListForClass(Object->GetClass());
			for (TWeakPtr<IAssetTypeActions> AssetTypeActionsRef : AssetTypeActionsList)
			{
				IAssetTypeActions* AssetTypeActions = AssetTypeActionsRef.Pin().Get();
				if (AssetTypeActions == nullptr)
				{
					continue;
				}
				if (AssetTypeActions == this)
				{
					continue;
				}

				AssetTypeActions->OpenAssetEditor(InObjects, EditWithinLevelEditor);
			}
		}
	}	
}

uint32 FAssetTypeActions_ExtendBehaviorTree::GetCategories()
{
	IAIModule& AIModule = FModuleManager::GetModuleChecked<IAIModule>("AIModule").Get();
	return AIModule.GetAIAssetCategoryBit();
}

#undef LOCTEXT_NAMESPACE
