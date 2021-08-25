// Copyright RadTuna. All Rights Reserved.

// Primary Include
#include "BlackboardConstantEditor.h"

// User Include
#include "BehaviorTreeEditorTabs.h"
#include "BlackboardConstant.h"
#include "DetailCustomizations/BlackboardConstantDetails.h"


#define LOCTEXT_NAMESPACE "BlackboardConstantEditor"

const FName FBlackboardConstantEditor::BlackboardConstantEditorID(TEXT("BlackboardConstantEditor"));

FBlackboardConstantEditor::FBlackboardConstantEditor()
	: FAssetEditorToolkit()
{
}

FBlackboardConstantEditor::~FBlackboardConstantEditor()
{
}

void FBlackboardConstantEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("BlackboardConstantEditor_WorkspaceMenu", "Blackboard Constant Editor"));
	
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
	
	InTabManager->RegisterTabSpawner(
		FBlackboardConstantEditorTabs::DetailsID,
		FOnSpawnTab::CreateSP(this, &FBlackboardConstantEditor::SpawnDetailsTab))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef())
		.SetDisplayName(LOCTEXT("BlackboardConstantEditor_DetailTabName", "Details"));
}

void FBlackboardConstantEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(FBlackboardConstantEditorTabs::DetailsID);
}

void FBlackboardConstantEditor::InitBlackboardConstantEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* InObject)
{
	UBlackboardConstant* BlackboardConstantToEdit = Cast<UBlackboardConstant>(InObject);
	if (BlackboardConstantToEdit != nullptr)
	{
		BlackboardConstant = BlackboardConstantToEdit;
	}

	DetailsView = SpawnDetailsView();
	
	TSharedRef<FTabManager::FLayout> EditorLayout = MakeEditorLayout();
	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, BlackboardConstantEditorID, EditorLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, InObject);

	if (DetailsView.IsValid())
	{
		DetailsView->SetObject(InObject);
	}
}

FName FBlackboardConstantEditor::GetToolkitFName() const
{
	return FName("Blackboard Constant");
}

FText FBlackboardConstantEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "BlackboardConstant");
}

FString FBlackboardConstantEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "BlackboardConstant ").ToString();
}

FLinearColor FBlackboardConstantEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor( 0.0f, 0.0f, 0.2f, 0.5f );
}

FText FBlackboardConstantEditor::GetToolkitName() const
{
	return FAssetEditorToolkit::GetToolkitName();
}

FText FBlackboardConstantEditor::GetToolkitToolTipText() const
{
	return FAssetEditorToolkit::GetToolkitToolTipText();
}

void FBlackboardConstantEditor::NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged)
{
	FNotifyHook::NotifyPostChange(PropertyChangedEvent, PropertyThatChanged);

	DetailsView->SetObject(BlackboardConstant, true);
}

TSharedPtr<IDetailsView> FBlackboardConstantEditor::SpawnDetailsView()
{
	const bool bIsUpdatable = false;
	const bool bIsLockable = false;
	const bool bAllowSearch = true;
	const bool bHideSelectionTip = true;

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs(bIsUpdatable, bIsLockable, bAllowSearch, FDetailsViewArgs::HideNameArea, bHideSelectionTip);
	DetailsViewArgs.NotifyHook = this;
	TSharedPtr<IDetailsView> NewDetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);

	FOnGetDetailCustomizationInstance LayoutDetails = FOnGetDetailCustomizationInstance::CreateStatic(FBlackboardConstantDetails::MakeInstance);
	NewDetailsView->RegisterInstancedCustomPropertyLayout(UBlackboardConstant::StaticClass(), LayoutDetails);

	return NewDetailsView;
}

TSharedRef<FTabManager::FLayout> FBlackboardConstantEditor::MakeEditorLayout()
{
	TSharedRef<FTabManager::FLayout> EditorLayout = FTabManager::NewLayout("BlackboardConstantEditor_Layout_v1")
	->AddArea
	(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
		->Split
		(
			FTabManager::NewStack()
			->SetSizeCoefficient(0.1f)
			->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
			->SetHideTabWell(true)
		)
		->Split
		(
			FTabManager::NewStack()
			->SetSizeCoefficient(0.9f)
			->AddTab(FBlackboardConstantEditorTabs::DetailsID, ETabState::OpenedTab)
			->SetHideTabWell(true)
		)
	);

	return EditorLayout;
}

TSharedRef<SDockTab> FBlackboardConstantEditor::SpawnDetailsTab(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == FBlackboardConstantEditorTabs::DetailsID);
	return SNew(SDockTab)
		[
			DetailsView.ToSharedRef()
		];
}

#undef LOCTEXT_NAMESPACE
