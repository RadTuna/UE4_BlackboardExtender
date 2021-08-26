// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"
#include "BehaviorTree/BlackboardData.h"

class IDetailLayoutBuilder;
class SBehaviorTreeBlackboardView;

/** Delegate used to retrieve current blackboard selection */
DECLARE_DELEGATE_RetVal_OneParam(int32, FOnGetSelectedBlackboardItemIndex, bool& /* bIsInherited */);

class FBlackboardDataDetails : public IDetailCustomization
{
public:
	FBlackboardDataDetails(TWeakPtr<SBehaviorTreeBlackboardView> InBlackboardView, FOnGetSelectedBlackboardItemIndex InOnGetSelectedBlackboardItemIndex)
		: OnGetSelectedBlackboardItemIndex(InOnGetSelectedBlackboardItemIndex)
		, BlackboardViewCached(InBlackboardView)
		, BlackboardDataCached(nullptr)
		, KeysPropertyHandleCached(nullptr)
		, CurrentCategorySelection(INDEX_NONE)
	{}

	/** Makes a new instance of this detail layout class for a specific detail view requesting it */
	static TSharedRef<IDetailCustomization> MakeInstance(TWeakPtr<SBehaviorTreeBlackboardView> InBlackboardView, FOnGetSelectedBlackboardItemIndex InOnGetSelectedBlackboardItemIndex);

	/** IDetailCustomization interface */
	virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;

private:
	void HandleOnCommittedEntryName(const FText& InName, ETextCommit::Type CommitType);
	bool HandleOnVerifyEntryNameChanged(const FText& InNewText, FText& OutErrorMessage);
	void HandleOnCommittedCategory(const FText& InCategory, ETextCommit::Type CommitType);
	ECheckBoxState HandleOnIsConstantChecked() const;
	void HandleOnConstantCheckStateChanged(ECheckBoxState InCheckState);

	void PostEditBlackboardProperty();

private:
	/** Delegate used to retrieve current blackboard selection */
	FOnGetSelectedBlackboardItemIndex OnGetSelectedBlackboardItemIndex;

	TWeakPtr<SBehaviorTreeBlackboardView> BlackboardViewCached;
	TWeakObjectPtr<UBlackboardData> BlackboardDataCached;
	TSharedPtr<IPropertyHandle> KeysPropertyHandleCached;
	
	int32 CurrentCategorySelection;
	bool bIsInheritedSelection;
};
