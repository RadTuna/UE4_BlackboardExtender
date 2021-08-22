// Fill out your copyright notice in the Description page of Project Settings.

// Primary Include
#include "BEBlackboardData.h"


UBEBlackboardData::UBEBlackboardData(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UBEBlackboardData::PostInitProperties()
{
	Super::PostInitProperties();
	
	UpdateParentCategories();
	CleanUpCategoryMap();
}

void UBEBlackboardData::PostLoad()
{
	Super::PostLoad();
	
	UpdateParentCategories();
	CleanUpCategoryMap();
}

#if WITH_EDITOR
void UBEBlackboardData::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UpdateParentCategories();
	PropagateChangeCategories();
	
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void UBEBlackboardData::AddUniqueCategory(const FBlackboardEntryIdentifier& Identifier, const FText& InCategory, bool bIsInheritKey)
{
	TMap<FBlackboardEntryIdentifier, FText>& TargetMap = bIsInheritKey ? ParentCategories : Categories;

	FText NewCategory = InCategory;
	const FString CategoryKey = InCategory.ToString();
	if (CategoryFilter.Contains(CategoryKey))
	{
		NewCategory = *CategoryFilter.Find(CategoryKey);
	}
	else
	{
		CategoryFilter.Add(CategoryKey, NewCategory);
	}
	
	TargetMap.Add(Identifier, NewCategory);
}

FText UBEBlackboardData::GetUniqueCategory(const FBlackboardEntryIdentifier& Identifier, bool bIsInheritKey)
{
	const TMap<FBlackboardEntryIdentifier, FText>& TargetMap = bIsInheritKey ? ParentCategories : Categories;

	FText OutCategory = FText::GetEmpty();
	if (TargetMap.Contains(Identifier))
	{
		OutCategory = *TargetMap.Find(Identifier);
	}
	
	return OutCategory;
}

void UBEBlackboardData::UpdateParentCategories()
{
	if (Parent == nullptr)
	{
		ParentCategories.Empty();
	}
	else
	{
		UBEBlackboardData* ParentBlackboard = Cast<UBEBlackboardData>(Parent);
		if (ParentBlackboard != nullptr)
		{
			ParentCategories.Empty();
			ParentCategories.Append(ParentBlackboard->ParentCategories);
			ParentCategories.Append(ParentBlackboard->Categories);
			
			CategoryFilter.Append(ParentBlackboard->CategoryFilter);
		}
	}
}

void UBEBlackboardData::PropagateChangeCategories()
{
	for (TObjectIterator<UBEBlackboardData> It; It; ++It)
	{
		if (It->Parent == this)
		{
			It->UpdateParentCategories();
			It->PropagateChangeCategories();
		}
	}
}

void UBEBlackboardData::CleanUpCategoryMap()
{
	TSet<FString> UniqueCategoryKeySet;
	for (TPair<FBlackboardEntryIdentifier, FText> Pair : ParentCategories)
	{
		UniqueCategoryKeySet.Add(Pair.Value.ToString());
	}
	for (TPair<FBlackboardEntryIdentifier, FText> Pair : Categories)
	{
		UniqueCategoryKeySet.Add(Pair.Value.ToString());
	}

	TArray<FString> PendingKillCategoryKeyList;
	for (TPair<FString, FText> Pair : CategoryFilter)
	{
		if (!UniqueCategoryKeySet.Contains(Pair.Key))
		{
			PendingKillCategoryKeyList.Add(Pair.Key);
		}
	}

	for (const FString& CategoryKey : PendingKillCategoryKeyList)
	{
		CategoryFilter.Remove(CategoryKey);
	}
}

