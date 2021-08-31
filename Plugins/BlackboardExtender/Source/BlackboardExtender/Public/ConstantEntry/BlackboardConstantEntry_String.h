// Copyright 2021 RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlackboardConstantEntry.h"
#include "BlackboardConstantEntry_String.generated.h"

UCLASS()
class BLACKBOARDEXTENDER_API UBlackboardConstantEntry_String : public UBlackboardConstantEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FString Data;

public:
	UBlackboardConstantEntry_String()
		: UBlackboardConstantEntry()
		, Data(TEXT(""))
	{
	}
	
	virtual ~UBlackboardConstantEntry_String() override {}
	
	virtual void ClearData() override { Data = TEXT(""); }
};
