// Copyright RadTuna. All Rights Reserved.

// Primary Include
#include "BEBlackboardData.h"

// User Include
#include "BlackboardConstant.h"


UBEBlackboardData::UBEBlackboardData(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UBEBlackboardData::PostInitProperties()
{
	Super::PostInitProperties();
	
	UpdateParentElements();
	UpdateConstantElements();
	CleanUpCategoryMap();
}

void UBEBlackboardData::PostLoad()
{
	Super::PostLoad();
	
	UpdateParentElements();
	UpdateConstantElements();
	CleanUpCategoryMap();
}

#if WITH_EDITOR
void UBEBlackboardData::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UpdateParentElements();
	UpdateConstantElements();
	PropagateChangeElements();
	
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void UBEBlackboardData::SetEntryName(const FName& OldEntryName, const FName& NewEntryName, bool bIsInherit)
{
	TArray<FBlackboardEntry>& CurrentEntries = bIsInherit ? ParentKeys : Keys;
	FBlackboardEntry* FoundEntry = CurrentEntries.FindByPredicate([&OldEntryName](const FBlackboardEntry& Entry)
	{
		return Entry.EntryName == OldEntryName;
	});

	if (FoundEntry != nullptr)
	{
		const FBlackboardEntryIdentifier OldIdentifier(*FoundEntry);
		FoundEntry->EntryName = FName(*NewEntryName.ToString());
		const FBlackboardEntryIdentifier NewIdentifier(*FoundEntry);
		
		if (Categories.Contains(OldIdentifier))
		{
			const FText CategoryKey = *Categories.Find(OldIdentifier);
			Categories.Remove(OldIdentifier);
			Categories.Add(NewIdentifier, CategoryKey);
		}

		if (ConstantMap.Contains(OldIdentifier))
		{
			const bool Constant = *ConstantMap.Find(OldIdentifier);
			ConstantMap.Remove(OldIdentifier);
			ConstantMap.Add(NewIdentifier, Constant);
		}
	}
}

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

void UBEBlackboardData::SetUniqueConstant(const FBlackboardEntryIdentifier& Identifier, bool bIsConstant, bool bIsInheritKey)
{
	TMap<FBlackboardEntryIdentifier, bool>& CurrentConstantMap = bIsInheritKey ? ParentConstantMap : ConstantMap;
	if (CurrentConstantMap.Contains(Identifier))
	{
		CurrentConstantMap.Add(Identifier, bIsConstant);
	}
}

const bool* UBEBlackboardData::GetUniqueConstant(const FBlackboardEntryIdentifier& Identifier, bool bIsInheritKey)
{
	const TMap<FBlackboardEntryIdentifier, bool>& CurrentConstantMap = bIsInheritKey ? ParentConstantMap : ConstantMap;
	const bool* OutConstant = nullptr;
	if (CurrentConstantMap.Contains(Identifier))
	{
		OutConstant = CurrentConstantMap.Find(Identifier);
	}

	return OutConstant;
}

#if WITH_EDITOR
bool UBEBlackboardData::CompareOrderFromIdentifier(const FBlackboardEntryIdentifier& InA, const FBlackboardEntryIdentifier& InB, bool bIsInherit)
{
	const TArray<FBlackboardEntryIdentifier> OrderList = bIsInherit ? ParentKeysOrder : KeysOrder;
	int32 IndexA = INDEX_NONE;
	for (int32 Index = 0; Index < OrderList.Num(); ++Index)
	{
		if (InA == OrderList[Index])
		{
			IndexA = Index;
			break;
		}
	}
	if (IndexA == INDEX_NONE)
	{
		return false;
	}

	int32 IndexB = INDEX_NONE;
	for (int32 Index = 0; Index < OrderList.Num(); ++Index)
	{
		if (InB == OrderList[Index])
		{
			IndexB = Index;
			break;
		}
	}
	if (IndexB == INDEX_NONE)
	{
		return true;
	}

	return IndexA < IndexB;
}
#endif

void UBEBlackboardData::UpdateParentElements()
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

			ParentKeysOrder.Empty();
			ParentKeysOrder.Append(ParentBlackboard->ParentKeysOrder);
			ParentKeysOrder.Append(ParentBlackboard->KeysOrder);

			ParentConstantMap.Empty();
			ParentConstantMap.Append(ParentBlackboard->ParentConstantMap);
			ParentConstantMap.Append(ParentBlackboard->ConstantMap);
		}
	}
}

void UBEBlackboardData::UpdateConstantElements()
{
	for (TObjectIterator<UBlackboardConstant> It; It; ++It)
	{
		if (It->BlackboardData == this)
		{
			It->UpdateConstantEntry();
		}
	}
}

void UBEBlackboardData::PropagateChangeElements()
{
	for (TObjectIterator<UBEBlackboardData> It; It; ++It)
	{
		if (It->Parent == this)
		{
			It->UpdateParentElements();
			It->UpdateConstantElements();
			
			It->PropagateChangeElements();
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

