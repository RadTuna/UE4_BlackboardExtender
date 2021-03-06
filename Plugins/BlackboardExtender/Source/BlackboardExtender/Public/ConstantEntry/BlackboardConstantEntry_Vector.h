// Copyright 2021 RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlackboardConstantEntry.h"
#include "BlackboardConstantEntry_Vector.generated.h"

UCLASS()
class BLACKBOARDEXTENDER_API UBlackboardConstantEntry_Vector : public UBlackboardConstantEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FVector Data;

public:
	UBlackboardConstantEntry_Vector()
		: UBlackboardConstantEntry()
		, Data(FVector::ZeroVector)
	{
	}
	
	virtual ~UBlackboardConstantEntry_Vector() override {}
	
	virtual void ClearData() override { Data = FVector::ZeroVector; }
};
