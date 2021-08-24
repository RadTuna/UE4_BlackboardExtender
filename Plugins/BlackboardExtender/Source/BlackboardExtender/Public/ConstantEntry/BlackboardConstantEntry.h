// Copyright RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BlackboardConstantEntry.generated.h"


USTRUCT()
struct FBlackboardConstantEntry
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	FName EntryName;

	UPROPERTY(VisibleAnywhere)
	UBlackboardKeyType* BlackboardEntryType;

public:
	FBlackboardConstantEntry()
		: EntryName(NAME_None)
		, BlackboardEntryType(nullptr)
	{
	}
	
	FBlackboardConstantEntry(const FName& InEntryName, UBlackboardKeyType* InKeyType)
		: EntryName(InEntryName)
		, BlackboardEntryType(InKeyType)
	{
	}

	virtual ~FBlackboardConstantEntry() {}

	virtual void ClearData() {}
};
