// Copyright 2021 RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlackboardConstantEntry.h"
#include "BlackboardConstantEntry_Bool.generated.h"

UCLASS()
class BLACKBOARDEXTENDER_API UBlackboardConstantEntry_Bool : public UBlackboardConstantEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	bool Data;

public:
	UBlackboardConstantEntry_Bool()
		: UBlackboardConstantEntry()
		, Data(false)
	{
	}
	
	virtual ~UBlackboardConstantEntry_Bool() override {}
	
	virtual void ClearData() override { Data = false; }
};