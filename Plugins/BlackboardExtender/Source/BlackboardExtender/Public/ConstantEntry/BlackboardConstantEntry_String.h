// Copyright RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlackboardConstantEntry.h"
#include "BlackboardConstantEntry_String.generated.h"

USTRUCT()
struct FBlackboardConstantEntry_String : public FBlackboardConstantEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	FString Data;

public:
	FBlackboardConstantEntry_String()
		: FBlackboardConstantEntry()
		, Data(TEXT(""))
	{
	}
	
	FBlackboardConstantEntry_String(const FName& InEntryName, UBlackboardKeyType* InKeyType)
		: FBlackboardConstantEntry(InEntryName, InKeyType)
		, Data(TEXT(""))
	{
	}
	
	virtual ~FBlackboardConstantEntry_String() override {}
	
	virtual void ClearData() override { Data = TEXT(""); }
};
