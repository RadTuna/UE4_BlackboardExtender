// Copyright RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlackboardConstantEntry.h"
#include "BlackboardConstantEntry_Rotator.generated.h"

USTRUCT()
struct FBlackboardConstantEntry_Rotator : public FBlackboardConstantEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	FRotator Data;

public:
	FBlackboardConstantEntry_Rotator()
		: FBlackboardConstantEntry()
		, Data(FRotator::ZeroRotator)
	{
	}
	
	FBlackboardConstantEntry_Rotator(const FName& InEntryName, UBlackboardKeyType* InKeyType)
		: FBlackboardConstantEntry(InEntryName, InKeyType)
		, Data(FRotator::ZeroRotator)
	{
	}
	
	virtual ~FBlackboardConstantEntry_Rotator() override {}
	
	virtual void ClearData() override { Data = FRotator::ZeroRotator; }
};
