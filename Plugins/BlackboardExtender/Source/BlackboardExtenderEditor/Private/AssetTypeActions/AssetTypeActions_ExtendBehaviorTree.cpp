// Copyright 2021 RadTuna. All Rights Reserved.

// Primary Include
#include "AssetTypeActions_ExtendBehaviorTree.h"

// Engine Include
#include "AIModule.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

// User Include
#include "BehaviorTreeEditor.h"
#include "BlackboardExtenderEditorModule.h"
#include "SBehaviorTreeDiff.h"


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

	for(auto Object : InObjects)
	{
		UBehaviorTree* BehaviorTree = Cast<UBehaviorTree>(Object);
		if(BehaviorTree != nullptr)
		{
			// check if we have an editor open for this BT's blackboard & use that if we can
			bool bFoundExisting = false;
			if(BehaviorTree->BlackboardAsset != nullptr)
			{
				const bool bFocusIfOpen = false;
				FBehaviorTreeEditor* ExistingInstance = static_cast<FBehaviorTreeEditor*>(GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->FindEditorForAsset(BehaviorTree->BlackboardAsset, bFocusIfOpen));
				if(ExistingInstance != nullptr && ExistingInstance->GetBehaviorTree() == nullptr)
				{
					ExistingInstance->InitBehaviorTreeEditor(Mode, EditWithinLevelEditor, BehaviorTree);
					bFoundExisting = true;
				}
			}
			
			if(!bFoundExisting)
			{
				FBlackboardExtenderEditorModule& BehaviorTreeEditorModule = FModuleManager::GetModuleChecked<FBlackboardExtenderEditorModule>("BlackboardExtenderEditor");
				TSharedRef<IBEBehaviorTreeEditor> NewEditor = BehaviorTreeEditorModule.CreateBehaviorTreeEditor(Mode, EditWithinLevelEditor, BehaviorTree);	
			}
		}
	}	
}

uint32 FAssetTypeActions_ExtendBehaviorTree::GetCategories()
{
	IAIModule& AIModule = FModuleManager::GetModuleChecked<IAIModule>("AIModule").Get();
	return AIModule.GetAIAssetCategoryBit();
}

void FAssetTypeActions_ExtendBehaviorTree::PerformAssetDiff(UObject* OldAsset, UObject* NewAsset, const FRevisionInfo& OldRevision, const FRevisionInfo& NewRevision) const
{
	UBehaviorTree* OldBehaviorTree = Cast<UBehaviorTree>(OldAsset);
	check(OldBehaviorTree != NULL);

	UBehaviorTree* NewBehaviorTree = Cast<UBehaviorTree>(NewAsset);
	check(NewBehaviorTree != NULL);

	// sometimes we're comparing different revisions of one single asset (other 
	// times we're comparing two completely separate assets altogether)
	bool bIsSingleAsset = (NewBehaviorTree->GetName() == OldBehaviorTree->GetName());

	FText WindowTitle = LOCTEXT("NamelessBehaviorTreeDiff", "Behavior Tree Diff");
	// if we're diffing one asset against itself 
	if (bIsSingleAsset)
	{
		// identify the assumed single asset in the window's title
		WindowTitle = FText::Format(LOCTEXT("Behavior Tree Diff", "{0} - Behavior Tree Diff"), FText::FromString(NewBehaviorTree->GetName()));
	}

	const TSharedPtr<SWindow> Window = SNew(SWindow)
		.Title(WindowTitle)
		.ClientSize(FVector2D(1000,800));

	Window->SetContent(SNew(SBehaviorTreeDiff)
		.BehaviorTreeOld(OldBehaviorTree)
		.BehaviorTreeNew(NewBehaviorTree)
		.OldRevision(OldRevision)
		.NewRevision(NewRevision)
		.ShowAssetNames(!bIsSingleAsset)
		.OpenInDefaults(const_cast<FAssetTypeActions_ExtendBehaviorTree*>(this), &FAssetTypeActions_ExtendBehaviorTree::OpenInDefaults));

	// Make this window a child of the modal window if we've been spawned while one is active.
	TSharedPtr<SWindow> ActiveModal = FSlateApplication::Get().GetActiveModalWindow();
	if ( ActiveModal.IsValid() )
	{
		FSlateApplication::Get().AddWindowAsNativeChild( Window.ToSharedRef(), ActiveModal.ToSharedRef());
	}
	else
	{
		FSlateApplication::Get().AddWindow(Window.ToSharedRef());
	}
}

void FAssetTypeActions_ExtendBehaviorTree::OpenInDefaults(UBehaviorTree* OldBehaviorTree, UBehaviorTree* NewBehaviorTree) const
{
	FString OldTextFilename = DumpAssetToTempFile(OldBehaviorTree);
	FString NewTextFilename = DumpAssetToTempFile(NewBehaviorTree);

	// Get diff program to use
	FString DiffCommand = GetDefault<UEditorLoadingSavingSettings>()->TextDiffToolPath.FilePath;

	FAssetToolsModule& AssetToolsModule = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");
	AssetToolsModule.Get().CreateDiffProcess(DiffCommand, OldTextFilename, NewTextFilename);
}

#undef LOCTEXT_NAMESPACE
