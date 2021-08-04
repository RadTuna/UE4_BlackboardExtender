// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FBlackboardExtenderEditorModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	TSharedPtr<class FBlackboardExtenderInstance> GetBlackboardExtenderInstance() const { return BlackboardExtenderInstance; }

private:
	TSharedPtr<class FBlackboardExtenderInstance> BlackboardExtenderInstance;

	TArray<TSharedPtr<class FAssetTypeActions_Base>> AssetTypeActionsList;
	
};
