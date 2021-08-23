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

public:
	FBlackboardEntryIdentifier()
		: EntryName(NAME_None)
	{
	}
	
	FBlackboardEntryIdentifier(const FBlackboardEntry& InEntry)
		: EntryName(InEntry.EntryName)
	{
	}

	FBlackboardEntryIdentifier(const FBlackboardEntryIdentifier& Other)
		: EntryName(Other.EntryName)
	{
	}

	bool operator==(const FBlackboardEntryIdentifier& Other) const
	{
		return (EntryName == Other.EntryName);
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

	virtual void PostInitProperties() override;
	virtual void PostLoad() override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	void AddUniqueCategory(const FBlackboardEntryIdentifier& Identifier, const FText& InCategory, bool bIsInheritKey);
	FText GetUniqueCategory(const FBlackboardEntryIdentifier& Identifier, bool bIsInheritKey);

private:
	void UpdateParentCategories();
	void PropagateChangeCategories();

	void CleanUpCategoryMap();
	
public:
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category=BlackboardCategory)
	TMap<FBlackboardEntryIdentifier, FText> ParentCategories;
	
	UPROPERTY(EditAnywhere, Category=BlackboardCategory)
	TMap<FBlackboardEntryIdentifier, FText> Categories;

	UPROPERTY(VisibleAnywhere, Category=BlackboardCategory)
	TMap<FString, FText> CategoryFilter;
#endif
};
