// Copyright RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlackboardConstantEntry.h"
#include "BlackboardConstantEntry_Vector.generated.h"

USTRUCT()
struct FBlackboardConstantEntry_Vector : public FBlackboardConstantEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	FVector Data;

public:
	FBlackboardConstantEntry_Vector()
		: FBlackboardConstantEntry()
		, Data(FVector::ZeroVector)
	{
	}
	
	FBlackboardConstantEntry_Vector(const FName& InEntryName, UBlackboardKeyType* InKeyType)
		: FBlackboardConstantEntry(InEntryName, InKeyType)
		, Data(FVector::ZeroVector)
	{
	}
	
	virtual ~FBlackboardConstantEntry_Vector() override {}
	
	virtual void ClearData() override { Data = FVector::ZeroVector; }
};
