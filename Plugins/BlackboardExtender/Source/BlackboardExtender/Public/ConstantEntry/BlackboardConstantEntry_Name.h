// Copyright RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlackboardConstantEntry.h"
#include "BlackboardConstantEntry_Name.generated.h"

USTRUCT()
struct FBlackboardConstantEntry_Name : public FBlackboardConstantEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	FName Data;

public:
	FBlackboardConstantEntry_Name()
		: FBlackboardConstantEntry()
		, Data(NAME_None)
	{
	}
	
	FBlackboardConstantEntry_Name(const FName& InEntryName, UBlackboardKeyType* InKeyType)
		: FBlackboardConstantEntry(InEntryName, InKeyType)
		, Data(NAME_None)
	{
	}
	
	virtual ~FBlackboardConstantEntry_Name() override {}
	
	virtual void ClearData() override { Data = NAME_None; }
};
