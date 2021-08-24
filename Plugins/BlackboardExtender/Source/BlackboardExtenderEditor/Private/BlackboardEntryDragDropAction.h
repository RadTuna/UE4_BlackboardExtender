// Copyright RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlueprintEditor.h"
#include "GraphEditorDragDropAction.h"


class FBlackboardEntryDragDropAction : public FGraphSchemaActionDragDropAction
{
public:
	DRAG_DROP_OPERATOR_TYPE(FMyBlueprintItemDragDropAction, FGraphSchemaActionDragDropAction)

	// FGraphEditorDragDropAction interface
	virtual FReply DroppedOnAction(TSharedRef<FEdGraphSchemaAction> Action) override;
	virtual FReply DroppedOnCategory(FText Category) override;
	virtual void HoverTargetChanged() override;

	static TSharedRef<FBlackboardEntryDragDropAction> New(TSharedPtr<FEdGraphSchemaAction> InAction, FName InEntryName, UStruct* InEntrySource)
	{
		TSharedRef<FBlackboardEntryDragDropAction> Operation = MakeShareable(new FBlackboardEntryDragDropAction);
		Operation->EntryName = InEntryName;
		Operation->EntrySource = InEntrySource;
		Operation->SourceAction = InAction;
		Operation->Construct();
		return Operation;
	}
	
protected:
	FBlackboardEntryDragDropAction();

	void SetFeedbackMessageError(const FText& Message);
	void SetFeedbackMessageOK(const FText& Message);

protected:
	FName EntryName;
	TWeakObjectPtr<UStruct> EntrySource;
	
};
