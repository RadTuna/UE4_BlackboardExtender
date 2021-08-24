// Copyright RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlackboardConstantEntry.h"
#include "BlackboardConstantEntry_Int.generated.h"

USTRUCT()
struct FBlackboardConstantEntry_Int : public FBlackboardConstantEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	int32 Data;

public:
	FBlackboardConstantEntry_Int()
		: FBlackboardConstantEntry()
		, Data(0)
	{
	}
	
	FBlackboardConstantEntry_Int(const FName& InEntryName, UBlackboardKeyType* InKeyType)
		: FBlackboardConstantEntry(InEntryName, InKeyType)
		, Data(0)
	{
	}
	
	virtual ~FBlackboardConstantEntry_Int() override {}
	
	virtual void ClearData() override { Data = 0; }
};
