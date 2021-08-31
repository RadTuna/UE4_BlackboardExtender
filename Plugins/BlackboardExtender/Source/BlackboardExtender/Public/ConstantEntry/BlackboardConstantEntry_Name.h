// Copyright 2021 RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlackboardConstantEntry.h"
#include "BlackboardConstantEntry_Name.generated.h"

UCLASS()
class BLACKBOARDEXTENDER_API UBlackboardConstantEntry_Name : public UBlackboardConstantEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FName Data;

public:
	UBlackboardConstantEntry_Name()
		: UBlackboardConstantEntry()
		, Data(NAME_None)
	{
	}
	
	virtual ~UBlackboardConstantEntry_Name() override {}
	
	virtual void ClearData() override { Data = NAME_None; }
};
