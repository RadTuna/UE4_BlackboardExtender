// Copyright RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlackboardConstantEntry.h"
#include "BlackboardConstantEntry_Enum.generated.h"

UCLASS()
class BLACKBOARDEXTENDER_API UBlackboardConstantEntry_Enum : public UBlackboardConstantEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	uint8 Data;

public:
	UBlackboardConstantEntry_Enum()
		: UBlackboardConstantEntry()
		, Data(0)
	{
	}
	
	virtual ~UBlackboardConstantEntry_Enum() override {}
	
	virtual void ClearData() override { Data = 0; }
};
