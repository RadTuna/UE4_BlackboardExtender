// Copyright RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlackboardConstantEntry.h"
#include "BlackboardConstantEntry_Enum.generated.h"

USTRUCT()
struct FBlackboardConstantEntry_Enum : public FBlackboardConstantEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	uint8 Data;

public:
	FBlackboardConstantEntry_Enum()
		: FBlackboardConstantEntry()
		, Data(0)
	{
	}
	
	FBlackboardConstantEntry_Enum(const FName& InEntryName, UBlackboardKeyType* InKeyType)
		: FBlackboardConstantEntry(InEntryName, InKeyType)
		, Data(0)
	{
	}
	
	virtual ~FBlackboardConstantEntry_Enum() override {}
	
	virtual void ClearData() override { Data = 0; }
};
