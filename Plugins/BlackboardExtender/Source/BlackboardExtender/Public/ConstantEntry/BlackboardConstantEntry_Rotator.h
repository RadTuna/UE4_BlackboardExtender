// Copyright RadTuna. All Rights Reserved.

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
	
	UBlackboardConstantEntry_Rotator(const FName& InEntryName, UBlackboardKeyType* InKeyType)
		: UBlackboardConstantEntry(InEntryName, InKeyType)
		, Data(FRotator::ZeroRotator)
	{
	}
	
	virtual ~UBlackboardConstantEntry_Rotator() override {}
	
	virtual void ClearData() override { Data = FRotator::ZeroRotator; }
};
