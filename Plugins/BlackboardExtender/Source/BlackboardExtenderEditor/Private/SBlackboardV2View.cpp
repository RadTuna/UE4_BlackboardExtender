// Fill out your copyright notice in the Description page of Project Settings.

// Primary Include
#include "SBlackboardV2View.h"

// Engine Include
#include "SlateOptMacros.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

#define LOCTEXT_NAMESPACE "SBlackboardV2View"

FName FEdGraphSchemaAction_BlackboardV2Entry::StaticGetTypeId()
{
	static FName Type("FEdGraphSchemaAction_BlackboardV2Entry");
	return Type; 
}

FName FEdGraphSchemaAction_BlackboardV2Entry::GetTypeId() const
{
	return StaticGetTypeId();
}

FEdGraphSchemaAction_BlackboardV2Entry::FEdGraphSchemaAction_BlackboardV2Entry(UBlackboardData* InBlackboardData, FBlackboardEntry& InKey, bool bInIsInherited)
	: FEdGraphSchemaAction_Dummy()
	, BlackboardData(InBlackboardData)
	, Key(InKey)
	, bIsInherited(bIsInherited)
	, bIsNew(false)
{
	check(BlackboardData != nullptr);
	Update();
}

void FEdGraphSchemaAction_BlackboardV2Entry::Update()
{
	UpdateSearchData(
		FText::FromName(Key.EntryName),
		FText::Format(LOCTEXT("BlackboardV2EntryFormat", "{0} '{1}'"),
			Key.KeyType ? Key.KeyType->GetClass()->GetDisplayNameText() : LOCTEXT("NullKeyDesc", "None"),
			FText::FromName(Key.EntryName)), FText(), FText());
	SectionID = bIsInherited ? EBlackboardSectionTitles::InheritedKeys : EBlackboardSectionTitles::Keys;
}

void SBlackboardV2View::AddReferencedObjects(FReferenceCollector& Collector)
{
	if (BlackboardData != nullptr)
	{
		Collector.AddReferencedObject(BlackboardData);
	}
}

void SBlackboardV2View::Construct(const FArguments& InArgs, TSharedRef<FUICommandList> InCommandList, UBlackboardDataV2* InBlackboardData)
{
	OnEntrySelected = InArgs._OnEntrySelected;
	OnBlackboardKeyChanged = InArgs._OnBlackboardChanged;

	BlackboardData = InBlackboardData;

	ChildSlot
	[
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		.AutoHeight()
		.Padding(4.f)
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Left)
			[
				SNew(SButton)
				.ButtonStyle(FEditorStyle::Get(), "ToolbarComboButton")
				.ForegroundColor(FSlateColor::UseForeground())
				.OnPressed(FSimpleDelegate::CreateSP(this, &SBlackboardV2View::HandleCreateBlackboardEntry))
			]
		]

		+SVerticalBox::Slot()
		.FillHeight(1.f)
		[
			SAssignNew(GraphActionMenu, SGraphActionMenu, InArgs._IsReadOnly)
			.OnCreateWidgetForAction(this, &SBlackboardV2View::HandleCreateWidgetForAction)
			.OnCollectAllActions(this, &SBlackboardV2View::HandleCollectAllActions)
			.OnGetSectionTitle(this, &SBlackboardV2View::HandleGetSectionTitle)
			.OnActionSelected(this, &SBlackboardV2View::HandleActionSelected)
			.OnContextMenuOpening(this, &SBlackboardV2View::HandleContextMenuOpening, InCommandList)
			.OnActionMatchesName(this, &SBlackboardV2View::HandleActionMatchesName)
			.OnActionDragged(this, &SBlackboardV2View::HandleActionDragged)
			.AlphaSortItems(false)
			.AutoExpandActionMenu(true)
			.UseSectionStyling(true)
		]
	];
}

void SBlackboardV2View::HandleCreateBlackboardEntry()
{
	FText DialogText = FText::FromString(TEXT("Create Blackboard Entry!"));
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

TSharedRef<SWidget> SBlackboardV2View::HandleCreateWidgetForAction(FCreateWidgetForActionData* const InCreateData)
{
}

void SBlackboardV2View::HandleCollectAllActions(FGraphActionListBuilderBase& GraphActionListBuilder)
{
}

FText SBlackboardV2View::HandleGetSectionTitle(int32 SectionID)
{
}

void SBlackboardV2View::HandleActionSelected(const TArray<TSharedPtr<FEdGraphSchemaAction>>& SelectedActions, ESelectInfo::Type InSelectionType)
{
}

TSharedPtr<SWidget> SBlackboardV2View::HandleContextMenuOpening(TSharedRef<FUICommandList> ToolkitCommands)
{
}

bool SBlackboardV2View::HandleActionMatchesName(FEdGraphSchemaAction* InAction, const FName& InName)
{
}

FReply SBlackboardV2View::HandleActionDragged(const TArray<TSharedPtr<FEdGraphSchemaAction>>& InActions, const FPointerEvent& MouseEvent)
{
}

#undef LOCTEXT_NAMESPACE

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
