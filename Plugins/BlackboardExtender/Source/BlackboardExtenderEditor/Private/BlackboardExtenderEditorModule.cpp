// Copyright Epic Games, Inc. All Rights Reserved.

// Primary Include
#include "BlackboardExtenderEditorModule.h"

// Engine Include
#include "AssetToolsModule.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BEBehaviorTreeDecoratorGraphNode_Decorator.h"
#include "BEBehaviorTreeGraphNode.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BehaviorTree/Decorators/BTDecorator_BlueprintBase.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "EdGraphUtilities.h"
#include "IAssetTools.h"


// User Include
#include "AssetTypeActions/AssetTypeActions_ExtendBehaviorTree.h"
#include "AssetTypeActions/AssetTypeActions_ExtendBlackboard.h"
#include "BehaviorTreeEditor.h"
#include "BlackboardConstantEditor.h"
#include "DetailCustomizations/BehaviorDecoratorDetails.h"
#include "DetailCustomizations/BlackboardDecoratorDetails.h"
#include "DetailCustomizations/BlackboardSelectorDetails.h"
#include "SGraphNode_BehaviorTree.h"
#include "SGraphNode_Decorator.h"
#include "AssetTypeActions/AssetTypeActions_BlackboardConstant.h"


#define LOCTEXT_NAMESPACE "FBlackboardExtenderEditorModule"

const FName FBlackboardExtenderEditorModule::BlackboardExtenderEditorAppIdentifier(TEXT("BlackboardExtenderEditorApp"));

class FBEGraphPanelNodeFactory_BehaviorTree : public FGraphPanelNodeFactory
{
	virtual TSharedPtr<class SGraphNode> CreateNode(UEdGraphNode* Node) const override
	{
		if (UBEBehaviorTreeGraphNode* BTNode = Cast<UBEBehaviorTreeGraphNode>(Node))
		{
			return SNew(SGraphNode_BehaviorTree, BTNode);
		}

		if (UBEBehaviorTreeDecoratorGraphNode_Decorator* InnerNode = Cast<UBEBehaviorTreeDecoratorGraphNode_Decorator>(Node))
		{
			return SNew(SGraphNode_Decorator, InnerNode);
		}

		return NULL;
	}
};

TSharedPtr<FGraphPanelNodeFactory> GraphPanelNodeFactory_BehaviorTree;

void FBlackboardExtenderEditorModule::StartupModule()
{
	MenuExtensibilityManager = MakeShareable(new FExtensibilityManager);
	ToolBarExtensibilityManager = MakeShareable(new FExtensibilityManager);
	
	GraphPanelNodeFactory_BehaviorTree = MakeShareable(new FBEGraphPanelNodeFactory_BehaviorTree());
	FEdGraphUtilities::RegisterVisualNodeFactory(GraphPanelNodeFactory_BehaviorTree);
	
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

	TSharedPtr<FAssetTypeActions_BlackboardConstant> BlackboardConstantAssetTypeActions = MakeShared<FAssetTypeActions_BlackboardConstant>();
	AssetTypeActionsList.Add(BlackboardConstantAssetTypeActions);
	AssetToolsModule.RegisterAssetTypeActions(BlackboardConstantAssetTypeActions.ToSharedRef());

	// Unregister the details customizer
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomPropertyTypeLayout("BlackboardKeySelector");
	PropertyModule.UnregisterCustomClassLayout("BTDecorator_Blackboard");
	PropertyModule.UnregisterCustomClassLayout("BTDecorator");
	PropertyModule.NotifyCustomizationModuleChanged();
	
	// Register the details customizer
	PropertyModule.RegisterCustomPropertyTypeLayout("BlackboardKeySelector",FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FBlackboardSelectorDetails::MakeInstance));
	PropertyModule.RegisterCustomClassLayout("BTDecorator_Blackboard", FOnGetDetailCustomizationInstance::CreateStatic(&FBlackboardDecoratorDetails::MakeInstance));
	PropertyModule.RegisterCustomClassLayout("BTDecorator", FOnGetDetailCustomizationInstance::CreateStatic(&FBehaviorDecoratorDetails::MakeInstance));
	PropertyModule.NotifyCustomizationModuleChanged();
}

void FBlackboardExtenderEditorModule::ShutdownModule()
{
	if (!UObjectInitialized())
	{
		return;
	}

	MenuExtensibilityManager.Reset();
	ToolBarExtensibilityManager.Reset();
	ClassCache.Reset();
	
	if ( GraphPanelNodeFactory_BehaviorTree.IsValid() )
	{
		FEdGraphUtilities::UnregisterVisualNodeFactory(GraphPanelNodeFactory_BehaviorTree);
		GraphPanelNodeFactory_BehaviorTree.Reset();
	}
	
	// Unregister the BehaviorTree item data asset type actions
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for(auto& AssetTypeAction : AssetTypeActionsList)
		{
			if (AssetTypeAction.IsValid())
			{
				AssetToolsModule.UnregisterAssetTypeActions(AssetTypeAction.ToSharedRef());
			}	
		}			
	}
	AssetTypeActionsList.Empty();
	
	// Unregister the details customization
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomPropertyTypeLayout( "BlackboardKeySelector" );
		PropertyModule.UnregisterCustomClassLayout( "BTDecorator_Blackboard" );
		PropertyModule.UnregisterCustomClassLayout( "BTDecorator" );
		PropertyModule.NotifyCustomizationModuleChanged();
	}
}

TSharedRef<IBEBehaviorTreeEditor> FBlackboardExtenderEditorModule::CreateBehaviorTreeEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* Object)
{
	if (!ClassCache.IsValid())
	{
		ClassCache = MakeShareable(new FGraphNodeClassHelper(UBTNode::StaticClass()));
		FGraphNodeClassHelper::AddObservedBlueprintClasses(UBTTask_BlueprintBase::StaticClass());
		FGraphNodeClassHelper::AddObservedBlueprintClasses(UBTDecorator_BlueprintBase::StaticClass());
		FGraphNodeClassHelper::AddObservedBlueprintClasses(UBTService_BlueprintBase::StaticClass());
		ClassCache->UpdateAvailableBlueprintClasses();
	}

	TSharedRef<FBehaviorTreeEditor> NewBehaviorTreeEditor(new FBehaviorTreeEditor());
	NewBehaviorTreeEditor->InitBehaviorTreeEditor(Mode, InitToolkitHost, Object);
	return NewBehaviorTreeEditor;
}

void FBlackboardExtenderEditorModule::CreateBlackboardConstantEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* Object)
{
	TSharedRef<FBlackboardConstantEditor> NewBlackboardConstantEditor(new FBlackboardConstantEditor());
	NewBlackboardConstantEditor->InitBlackboardConstantEditor(Mode, InitToolkitHost, Object);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBlackboardExtenderEditorModule, BlackboardExtenderEditor)
DEFINE_LOG_CATEGORY(LogBlackboardExtenderEditor);
