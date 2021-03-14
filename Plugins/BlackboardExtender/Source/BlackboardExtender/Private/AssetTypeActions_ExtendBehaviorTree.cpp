// Fill out your copyright notice in the Description page of Project Settings.

// Primary Include
#include "BlackboardExtender/Public/AssetTypeActions_ExtendBehaviorTree.h"

// Engine Include
#include "AIModule.h"
#include "BehaviorTreeEditorModule.h"
#include "BlackboardExtender.h"
#include "BlackboardExtenderInstance.h"
#include "BehaviorTree/BehaviorTree.h"


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
			
			FBlackboardExtenderModule& BlackboardExtenderModule = FModuleManager::GetModuleChecked<FBlackboardExtenderModule>("BlackboardExtender");
			TSharedPtr<FBlackboardExtenderInstance> BlackboardExtenderInstance = BlackboardExtenderModule.GetBlackboardExtenderInstance();

			BlackboardExtenderInstance->InitializeExtenderInstance(Object, NewEditor);
		}
        
		TArray<TWeakPtr<IAssetTypeActions>> AssetTypeActionsList = AssetToolsModule.Get().GetAssetTypeActionsListForClass(Object->GetClass());
		for (TWeakPtr<IAssetTypeActions> AssetTypeActions : AssetTypeActionsList)
		{
			if (AssetTypeActions.Pin().Get() != this)
			{
				AssetTypeActions.Pin()->OpenAssetEditor(InObjects, EditWithinLevelEditor);
				break;
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
