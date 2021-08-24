// Copyright RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlackboardConstantEntry.h"
#include "BlackboardConstantEntry_Class.generated.h"

USTRUCT()
struct FBlackboardConstantEntry_Class : public FBlackboardConstantEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	UClass* Data;

public:
	FBlackboardConstantEntry_Class()
		: FBlackboardConstantEntry()
		, Data(nullptr)
	{
	}
	
	FBlackboardConstantEntry_Class(const FName& InEntryName, UBlackboardKeyType* InKeyType)
		: FBlackboardConstantEntry(InEntryName, InKeyType)
		, Data(nullptr)
	{
	}
	
	virtual ~FBlackboardConstantEntry_Class() override {}
	
	virtual void ClearData() override { Data = nullptr; }
};
