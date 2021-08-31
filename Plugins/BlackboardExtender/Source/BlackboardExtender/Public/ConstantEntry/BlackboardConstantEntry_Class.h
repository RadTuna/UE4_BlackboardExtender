// Copyright 2021 RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlackboardConstantEntry.h"
#include "BlackboardConstantEntry_Class.generated.h"

UCLASS()
class BLACKBOARDEXTENDER_API UBlackboardConstantEntry_Class : public UBlackboardConstantEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	UClass* Data;

public:
	UBlackboardConstantEntry_Class()
		: UBlackboardConstantEntry()
		, Data(nullptr)
	{
	}
	
	virtual ~UBlackboardConstantEntry_Class() override {}
	
	virtual void ClearData() override { Data = nullptr; }
};
