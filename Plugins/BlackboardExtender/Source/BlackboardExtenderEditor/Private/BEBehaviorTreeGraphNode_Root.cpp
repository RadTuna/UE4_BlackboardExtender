// Copyright Epic Games, Inc. All Rights Reserved.

#include "BEBehaviorTreeGraphNode_Root.h"
#include "UObject/UObjectIterator.h"
#include "BEBehaviorTreeEditorTypes.h"
#include "BEBehaviorTreeGraph.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

UBEBehaviorTreeGraphNode_Root::UBEBehaviorTreeGraphNode_Root(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsReadOnly = true;
}

void UBEBehaviorTreeGraphNode_Root::PostPlacedNewNode()
{
	Super::PostPlacedNewNode();

	// pick first available blackboard asset, hopefully something will be loaded...
	for (FThreadSafeObjectIterator It(UBlackboardData::StaticClass()); It; ++It)
	{
		UBlackboardData* TestOb = (UBlackboardData*)*It;
		if (!TestOb->HasAnyFlags(RF_ClassDefaultObject))
		{
			BlackboardAsset = TestOb;
			UpdateBlackboard();
			break;
		}
	}
}

void UBEBehaviorTreeGraphNode_Root::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, UBEBehaviorTreeEditorTypes::PinCategory_SingleComposite, TEXT("In"));
}

FText UBEBehaviorTreeGraphNode_Root::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return NSLOCTEXT("BlackboardExtenderEditor", "Root", "ROOT");
}

FName UBEBehaviorTreeGraphNode_Root::GetNameIcon() const
{
	return FName("BTEditor.Graph.BTNode.Root.Icon");
}

FText UBEBehaviorTreeGraphNode_Root::GetTooltipText() const
{
	return UEdGraphNode::GetTooltipText();
}

void UBEBehaviorTreeGraphNode_Root::PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property &&
		PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UBEBehaviorTreeGraphNode_Root, BlackboardAsset))
	{
		UpdateBlackboard();
	}
}

void UBEBehaviorTreeGraphNode_Root::PostEditUndo()
{
	Super::PostEditUndo();
	UpdateBlackboard();
}

FText UBEBehaviorTreeGraphNode_Root::GetDescription() const
{
	return FText::FromString(GetNameSafe(BlackboardAsset));
}

void UBEBehaviorTreeGraphNode_Root::UpdateBlackboard()
{
	UBEBehaviorTreeGraph* MyGraph = GetBehaviorTreeGraph();
	UBehaviorTree* BTAsset = Cast<UBehaviorTree>(MyGraph->GetOuter());
	if (BTAsset && BTAsset->BlackboardAsset != BlackboardAsset)
	{
		BTAsset->BlackboardAsset = BlackboardAsset;
		MyGraph->UpdateBlackboardChange();
	}
}
