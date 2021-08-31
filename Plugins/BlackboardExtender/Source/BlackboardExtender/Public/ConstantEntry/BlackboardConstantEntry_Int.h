// Copyright 2021 RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlackboardConstantEntry.h"
#include "BlackboardConstantEntry_Int.generated.h"

UCLASS()
class BLACKBOARDEXTENDER_API UBlackboardConstantEntry_Int : public UBlackboardConstantEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	int32 Data;

public:
	UBlackboardConstantEntry_Int()
		: UBlackboardConstantEntry()
		, Data(0)
	{
	}
	
	virtual ~UBlackboardConstantEntry_Int() override {}
	
	virtual void ClearData() override { Data = 0; }
};
