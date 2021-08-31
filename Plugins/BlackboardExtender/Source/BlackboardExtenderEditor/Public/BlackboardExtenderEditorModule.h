// Copyright 2021 RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "IBEBehaviorTreeEditor.h"


DECLARE_LOG_CATEGORY_EXTERN(LogBlackboardExtenderEditor, Log, All);

class FToolBarBuilder;
class FMenuBuilder;
class FBlackboardExtenderEditorModule
	: public IModuleInterface
	, public IHasMenuExtensibility
	, public IHasToolBarExtensibility
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual TSharedRef<IBEBehaviorTreeEditor> CreateBehaviorTreeEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, class UObject* Object);
	virtual void CreateBlackboardConstantEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, class UObject* Object);
	
	virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override { return MenuExtensibilityManager; }
	virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override { return ToolBarExtensibilityManager; }
	
	TSharedPtr<struct FGraphNodeClassHelper> GetClassCache() { return ClassCache; }

public:
	static const FName BlackboardExtenderEditorAppIdentifier;

private:
	TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;
	TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;
	
	TArray<TSharedPtr<class FAssetTypeActions_Base>> AssetTypeActionsList;
	TSharedPtr<struct FGraphNodeClassHelper> ClassCache;
	
};
