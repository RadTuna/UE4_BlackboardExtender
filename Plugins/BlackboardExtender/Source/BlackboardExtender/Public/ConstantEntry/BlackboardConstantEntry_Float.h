// Copyright RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlackboardConstantEntry.h"
#include "BlackboardConstantEntry_Float.generated.h"

USTRUCT()
struct FBlackboardConstantEntry_Float : public FBlackboardConstantEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	float Data;

public:
	FBlackboardConstantEntry_Float()
		: FBlackboardConstantEntry()
		, Data(0.f)
	{
	}
	
	FBlackboardConstantEntry_Float(const FName& InEntryName, UBlackboardKeyType* InKeyType)
		: FBlackboardConstantEntry(InEntryName, InKeyType)
		, Data(0.f)
	{
	}
	
	virtual ~FBlackboardConstantEntry_Float() override {}
	
	virtual void ClearData() override { Data = 0.f; }
};
