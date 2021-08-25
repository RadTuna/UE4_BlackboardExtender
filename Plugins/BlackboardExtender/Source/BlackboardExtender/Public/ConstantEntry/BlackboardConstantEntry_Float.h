// Copyright RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlackboardConstantEntry.h"
#include "BlackboardConstantEntry_Float.generated.h"

UCLASS()
class BLACKBOARDEXTENDER_API UBlackboardConstantEntry_Float : public UBlackboardConstantEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	float Data;

public:
	UBlackboardConstantEntry_Float()
		: UBlackboardConstantEntry()
		, Data(0.f)
	{
	}
	
	UBlackboardConstantEntry_Float(const FName& InEntryName, UBlackboardKeyType* InKeyType)
		: UBlackboardConstantEntry(InEntryName, InKeyType)
		, Data(0.f)
	{
	}
	
	virtual ~UBlackboardConstantEntry_Float() override {}
	
	virtual void ClearData() override { Data = 0.f; }
};
