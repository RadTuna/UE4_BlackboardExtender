// Copyright 2021 RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlackboardConstantEntry.h"
#include "BlackboardConstantEntry_Object.generated.h"

UCLASS()
class BLACKBOARDEXTENDER_API UBlackboardConstantEntry_Object : public UBlackboardConstantEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	UObject* Data;

public:
	UBlackboardConstantEntry_Object()
		: UBlackboardConstantEntry()
		, Data(nullptr)
	{
	}
	
	virtual ~UBlackboardConstantEntry_Object() override {}
	
	virtual void ClearData() override { Data = nullptr; }
};
