// Fill out your copyright notice in the Description page of Project Settings.

// Primary Include
#include "SBlackboardV2Item.h"

// Engine Include
#include "SlateOptMacros.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SBlackboardV2Item::Construct(const FArguments& InArgs, FCreateWidgetForActionData* const InCreateData)
{
	OnBlackboardKeyChanged = InArgs._OnBlackboardKeyChanged;

	const FSlateFontInfo NameFont = FCoreStyle::GetDefaultFontStyle("Regular", 10);

	check(InCreateData);
	check(InCreateData->Action.IsValid());

	TSharedPtr<FEdGraphSchemaAction> GraphAction = InCreateData->Action;
	check(GraphAction->Get)
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
