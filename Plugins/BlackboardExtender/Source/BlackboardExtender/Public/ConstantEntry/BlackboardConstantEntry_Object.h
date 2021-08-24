// Copyright RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlackboardConstantEntry.h"
#include "BlackboardConstantEntry_Object.generated.h"

USTRUCT()
struct FBlackboardConstantEntry_Object : public FBlackboardConstantEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	UObject* Data;

public:
	FBlackboardConstantEntry_Object()
		: FBlackboardConstantEntry()
		, Data(nullptr)
	{
	}
	
	FBlackboardConstantEntry_Object(const FName& InEntryName, UBlackboardKeyType* InKeyType)
		: FBlackboardConstantEntry(InEntryName, InKeyType)
		, Data(nullptr)
	{
	}
	
	virtual ~FBlackboardConstantEntry_Object() override {}
	
	virtual void ClearData() override { Data = nullptr; }
};
