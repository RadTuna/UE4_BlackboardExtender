// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBlackboardV2View.h"
#include "SGraphPalette.h"

class BLACKBOARDEXTENDEREDITOR_API SBlackboardV2Item : public SGraphPaletteItem
{
public:
	SLATE_BEGIN_ARGS(SBlackboardV2Item) {}

		SLATE_EVENT(FOnBlackboardKeyChanged, OnBlackboardKeyChanged)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, FCreateWidgetForActionData* const InCreateData);

private:
	FOnBlackboardKeyChanged OnBlackboardKeyChanged;
	
};
