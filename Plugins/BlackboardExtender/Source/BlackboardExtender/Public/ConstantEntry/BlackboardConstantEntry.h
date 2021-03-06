// Copyright 2021 RadTuna. All Rights Reserved.

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

	UPROPERTY(EditAnywhere)
	bool bIsInheritEntry;
	
	UPROPERTY(EditAnywhere)
	FText Category;

public:
	UBlackboardConstantEntry()
		: EntryName(NAME_None)
		, BlackboardEntryType(EBlackboardKeyType::Unknown)
		, bIsInheritEntry(false)
#if WITH_EDITORONLY_DATA
		, Category(FText::GetEmpty())
#endif
	{
	}

	void Initialize(const FName& InEntryName, EBlackboardKeyType InKeyType, bool bIsInherit, const FText& InCategory)
	{
		EntryName = InEntryName;
		BlackboardEntryType = InKeyType;
		bIsInheritEntry = bIsInherit;
#if WITH_EDITORONLY_DATA
		Category = InCategory;
#endif
	}

	virtual ~UBlackboardConstantEntry() override {}

	virtual void ClearData() {}
};
