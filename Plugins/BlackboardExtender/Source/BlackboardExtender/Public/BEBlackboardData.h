// Copyright 2021 RadTuna. All Rights Reserved.

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

	void SetEntryName(const FName& OldEntryName, const FName& NewEntryName, bool bIsInherit);

	void AddUniqueCategory(const FBlackboardEntryIdentifier& Identifier, const FText& InCategory, bool bIsInheritKey);
	FText GetUniqueCategory(const FBlackboardEntryIdentifier& Identifier, bool bIsInheritKey);
	
	void SetUniqueConstant(const FBlackboardEntryIdentifier& Identifier, bool bIsConstant, bool bIsInheritKey);
	const bool* GetUniqueConstant(const FBlackboardEntryIdentifier& Identifier, bool bIsInheritKey);
	
	bool CompareOrderFromIdentifier(const FBlackboardEntryIdentifier& InA, const FBlackboardEntryIdentifier& InB, bool bIsInherit);
#endif
	
private:
	void UpdateParentElements();
	void UpdateConstantElements();
	void PropagateChangeElements();

	void CleanUpCategoryMap();
	
public:
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category=BlackboardCategory)
	TMap<FBlackboardEntryIdentifier, FText> ParentCategories;
	
	UPROPERTY(EditAnywhere, Category=BlackboardCategory)
	TMap<FBlackboardEntryIdentifier, FText> Categories;

	UPROPERTY(VisibleAnywhere, Category=BlackboardCategory)
	TMap<FString, FText> CategoryFilter;

	UPROPERTY(VisibleAnywhere, Category=BlackboardCategory)
	TArray<FBlackboardEntryIdentifier> ParentKeysOrder;

	UPROPERTY(VisibleAnywhere, Category=BlackboardCategory)
	TArray<FBlackboardEntryIdentifier> KeysOrder;

	UPROPERTY(VisibleAnywhere, Category=BlackboardCategory)
	TMap<FBlackboardEntryIdentifier, bool> ParentConstantMap;
	
	UPROPERTY(VisibleAnywhere, Category=BlackboardCategory)
	TMap<FBlackboardEntryIdentifier, bool> ConstantMap;
#endif
};
