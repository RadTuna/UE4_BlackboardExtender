// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGraphActionMenu.h"
#include "BehaviorTree/BlackboardData.h"
#include "Widgets/SCompoundWidget.h"


class UBlackboardDataV2;
struct FBlackboardEntry;

DECLARE_DELEGATE_TwoParams(FOnEntrySelected, const FBlackboardEntry*, bool);
DECLARE_DELEGATE_ThreeParams(FOnBlackboardKeyChanged, UBlackboardDataV2*, FName, bool)

namespace EBlackboardSectionTitles
{
	enum Type
	{
		InheritedKeys = 1,
		Keys,
	};
}

class FEdGraphSchemaAction_BlackboardV2Entry : public FEdGraphSchemaAction_Dummy
{
public:
	static FName StaticGetTypeId();
	virtual FName GetTypeId() const override;

	FEdGraphSchemaAction_BlackboardV2Entry( UBlackboardData* InBlackboardData, FBlackboardEntry& InKey, bool bInIsInherited );

	void Update();

	UBlackboardData* BlackboardData;
	FBlackboardEntry& Key;
	bool bIsInherited;
	bool bIsNew;
};

class BLACKBOARDEXTENDEREDITOR_API SBlackboardV2View : public SCompoundWidget, public FGCObject
{
public:
	SLATE_BEGIN_ARGS(SBlackboardV2View)
	{
		_IsReadOnly = true;
	}

		SLATE_EVENT(FOnEntrySelected, OnEntrySelected)
		SLATE_EVENT(FOnBlackboardKeyChanged, OnBlackboardChanged)
		SLATE_ARGUMENT(bool, IsReadOnly)

	SLATE_END_ARGS()

	// Implementation FGCObject interface
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	
	void Construct(const FArguments& InArgs, TSharedRef<FUICommandList> InCommandList, UBlackboardDataV2* InBlackboardData);

private:
	void HandleCreateBlackboardEntry();

	// GraphActionMenu callbacks...
	TSharedRef<SWidget> HandleCreateWidgetForAction(FCreateWidgetForActionData* const InCreateData);
	void HandleCollectAllActions(FGraphActionListBuilderBase& GraphActionListBuilder);
	FText HandleGetSectionTitle(int32 SectionID);
	void HandleActionSelected(const TArray<TSharedPtr<FEdGraphSchemaAction>>& SelectedActions, ESelectInfo::Type InSelectionType);
	TSharedPtr<SWidget> HandleContextMenuOpening(TSharedRef<FUICommandList> ToolkitCommands);
	bool HandleActionMatchesName(FEdGraphSchemaAction* InAction, const FName& InName);
	FReply HandleActionDragged(const TArray<TSharedPtr<FEdGraphSchemaAction>>& InActions, const FPointerEvent& MouseEvent);
	
private:
	UBlackboardDataV2* BlackboardData;

	TSharedPtr<SGraphActionMenu> GraphActionMenu;

	FOnEntrySelected OnEntrySelected;
	FOnBlackboardKeyChanged OnBlackboardKeyChanged;

};
