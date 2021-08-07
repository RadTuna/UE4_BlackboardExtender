// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BlackboardData.h"
#include "BEBlackboardData.generated.h"


USTRUCT()
struct FBlackboardEntryIdentifier
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	FName EntryName;

	UPROPERTY(VisibleAnywhere)
	FName KeyTypeName;

public:
	FBlackboardEntryIdentifier()
		: EntryName(NAME_None)
		, KeyTypeName(NAME_None)
	{
	}
	
	FBlackboardEntryIdentifier(const FBlackboardEntry& InEntry)
		: EntryName(InEntry.EntryName)
		, KeyTypeName(NAME_None)
	{
		KeyTypeName = InEntry.KeyType->GetFName();
	}

	FBlackboardEntryIdentifier(const FBlackboardEntryIdentifier& Other)
		: EntryName(Other.EntryName)
		, KeyTypeName(Other.KeyTypeName)
	{
	}

	bool operator==(const FBlackboardEntryIdentifier& Other) const
	{
		return (EntryName == Other.EntryName) && (KeyTypeName == Other.KeyTypeName);
	}
};

FORCEINLINE uint32 GetTypeHash(const FBlackboardEntryIdentifier& InObject)
{
	return FCrc::MemCrc32(&InObject, sizeof(FBlackboardEntryIdentifier));
}

UCLASS()
class BLACKBOARDEXTENDER_API UBEBlackboardData : public UBlackboardData
{
	GENERATED_UCLASS_BODY()

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category=Blackboard)
	TMap<FBlackboardEntryIdentifier, FText> Categories;
#endif
};
