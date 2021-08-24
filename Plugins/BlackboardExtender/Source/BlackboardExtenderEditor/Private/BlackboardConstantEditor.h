// Copyright RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlackboardConstant.h"


class FBlackboardConstantEditor : public FAssetEditorToolkit
{
public:
	FBlackboardConstantEditor();
	virtual ~FBlackboardConstantEditor();

	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	
	void InitBlackboardConstantEditor( const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UObject* InObject );
	
	//~ Begin IToolkit Interface
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FText GetToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;

	TSharedPtr<IDetailsView> SpawnDetailsView();
	TSharedRef<FTabManager::FLayout> MakeEditorLayout();
	TSharedRef<SDockTab> SpawnDetailsTab(const FSpawnTabArgs& Args);

public:
	static const FName BlackboardConstantEditorID;

private:
	UBlackboardConstant* BlackboardConstant;
	TSharedPtr<IDetailsView> DetailsView;
	
};
