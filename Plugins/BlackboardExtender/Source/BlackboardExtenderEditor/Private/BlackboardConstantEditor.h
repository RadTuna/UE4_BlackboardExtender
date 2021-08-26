// Copyright RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlackboardConstant.h"


class FBlackboardConstantStyle
{
public:
	static void Initialize();
	static void Release();

	static FName GetStyleName();
	static ISlateStyle& Get();

private:
	static TSharedPtr<class FSlateStyleSet> Instance;
	
};

class FBlackboardConstantEditor : public FAssetEditorToolkit, public FNotifyHook
{
public:
	FBlackboardConstantEditor();
	virtual ~FBlackboardConstantEditor();

	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	
	void InitBlackboardConstantEditor( const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UObject* InObject );
	
	// IToolkit Interface
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FText GetToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;

	// FNotifyHook Interface
	virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;

private:
	TSharedPtr<IDetailsView> SpawnDetailsView();
	TSharedRef<FTabManager::FLayout> MakeEditorLayout();
	TSharedRef<SDockTab> SpawnDetailsTab(const FSpawnTabArgs& Args);

	void BindCommands();
	void RefreshConstantEntry();
	void ExtendToolbar(FToolBarBuilder& ToolBarBuilder);

public:
	static const FName BlackboardConstantEditorID;

private:
	UBlackboardConstant* BlackboardConstant;
	TSharedPtr<IDetailsView> DetailsView;
	
};
