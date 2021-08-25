// Copyright RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BlackboardConstantEntry.generated.h"


UCLASS()
class BLACKBOARDEXTENDER_API UBlackboardConstantEntry : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FName EntryName;

	UPROPERTY(EditAnywhere)
	UBlackboardKeyType* BlackboardEntryType;

public:
	UBlackboardConstantEntry()
		: EntryName(NAME_None)
		, BlackboardEntryType(nullptr)
	{
	}
	
	UBlackboardConstantEntry(const FName& InEntryName, UBlackboardKeyType* InKeyType)
		: EntryName(InEntryName)
		, BlackboardEntryType(InKeyType)
	{
	}

	virtual ~UBlackboardConstantEntry() override {}

	virtual void ClearData() {}
};
