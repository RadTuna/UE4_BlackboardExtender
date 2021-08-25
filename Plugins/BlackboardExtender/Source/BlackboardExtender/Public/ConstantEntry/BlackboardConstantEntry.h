// Copyright RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BlackboardConstantEntry.generated.h"


UENUM()
enum class EBlackboardKeyType : uint8
{
	Unknown,
	Bool,
	Class,
	Enum,
	Float,
	Int,
	Name,
	Object,
	Rotator,
	String,
	Vector
};

EBlackboardKeyType ConvertToEnumBlackboardKeyType(UBlackboardKeyType* InKeyType);

UCLASS()
class BLACKBOARDEXTENDER_API UBlackboardConstantEntry : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FName EntryName;

	UPROPERTY(EditAnywhere)
	EBlackboardKeyType BlackboardEntryType;

public:
	UBlackboardConstantEntry()
		: EntryName(NAME_None)
		, BlackboardEntryType(EBlackboardKeyType::Unknown)
	{
	}

	void Initialize(const FName& InEntryName, UBlackboardKeyType* InKeyType)
	{
		EntryName = InEntryName;
		BlackboardEntryType = ConvertToEnumBlackboardKeyType(InKeyType);
	}

	virtual ~UBlackboardConstantEntry() override {}

	virtual void ClearData() {}
};
