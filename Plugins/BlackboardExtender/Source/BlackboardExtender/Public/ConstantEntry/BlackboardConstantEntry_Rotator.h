// Copyright 2021 RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlackboardConstantEntry.h"
#include "BlackboardConstantEntry_Rotator.generated.h"

UCLASS()
class BLACKBOARDEXTENDER_API UBlackboardConstantEntry_Rotator : public UBlackboardConstantEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FRotator Data;

public:
	UBlackboardConstantEntry_Rotator()
		: UBlackboardConstantEntry()
		, Data(FRotator::ZeroRotator)
	{
	}
	
	virtual ~UBlackboardConstantEntry_Rotator() override {}
	
	virtual void ClearData() override { Data = FRotator::ZeroRotator; }
};
