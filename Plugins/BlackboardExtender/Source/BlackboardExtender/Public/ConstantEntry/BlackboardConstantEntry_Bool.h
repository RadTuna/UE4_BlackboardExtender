// Copyright RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlackboardConstantEntry.h"
#include "BlackboardConstantEntry_Bool.generated.h"

USTRUCT()
struct FBlackboardConstantEntry_Bool : public FBlackboardConstantEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	bool Data;

public:
	FBlackboardConstantEntry_Bool()
		: FBlackboardConstantEntry()
		, Data(false)
	{
	}
	
	FBlackboardConstantEntry_Bool(const FName& InEntryName, UBlackboardKeyType* InKeyType)
		: FBlackboardConstantEntry(InEntryName, InKeyType)
		, Data(false)
	{
	}
	
	virtual ~FBlackboardConstantEntry_Bool() override {}
	
	virtual void ClearData() override { Data = false; }
};