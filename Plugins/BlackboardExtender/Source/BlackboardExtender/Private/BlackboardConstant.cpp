// Copyright 2021 RadTuna. All Rights Reserved.

// Primary Include
#include "BlackboardConstant.h"

// Engine Include
#include "BEBlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

// User Include
#include "ConstantEntry/BlackboardConstantEntry_Bool.h"
#include "ConstantEntry/BlackboardConstantEntry_Class.h"
#include "ConstantEntry/BlackboardConstantEntry_Enum.h"
#include "ConstantEntry/BlackboardConstantEntry_Float.h"
#include "ConstantEntry/BlackboardConstantEntry_Int.h"
#include "ConstantEntry/BlackboardConstantEntry_Name.h"
#include "ConstantEntry/BlackboardConstantEntry_Object.h"
#include "ConstantEntry/BlackboardConstantEntry_Rotator.h"
#include "ConstantEntry/BlackboardConstantEntry_String.h"
#include "ConstantEntry/BlackboardConstantEntry_Vector.h"


void UBlackboardConstant::PostInitProperties()
{
	Super::PostInitProperties();

#if WITH_EDITOR
	UpdateConstantEntry();
#endif
}

void UBlackboardConstant::PostLoad()
{
	Super::PostLoad();

#if WITH_EDITOR
	UpdateConstantEntry();
#endif
}

#if WITH_EDITOR
void UBlackboardConstant::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UpdateConstantEntry();

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void UBlackboardConstant::InitBlackboardComponent(UBlackboardComponent* BlackboardComponent)
{
	if (BlackboardComponent == nullptr)
	{
		return;
	}

	for (UBlackboardConstantEntry* Entry : ConstantEntry)
	{
		check(Entry != nullptr);
		switch (Entry->BlackboardEntryType)
		{
			case EBlackboardKeyType::Bool:
				{
					const UBlackboardConstantEntry_Bool* CurrentEntry = Cast<UBlackboardConstantEntry_Bool>(Entry);
					BlackboardComponent->SetValueAsBool(CurrentEntry->EntryName, CurrentEntry->Data);
				}
				break;
			case EBlackboardKeyType::Class:
				{
					const UBlackboardConstantEntry_Class* CurrentEntry = Cast<UBlackboardConstantEntry_Class>(Entry);
					BlackboardComponent->SetValueAsClass(CurrentEntry->EntryName, CurrentEntry->Data);
				}
				break;
			case EBlackboardKeyType::Enum:
				{
					const UBlackboardConstantEntry_Enum* CurrentEntry = Cast<UBlackboardConstantEntry_Enum>(Entry);
					BlackboardComponent->SetValueAsEnum(CurrentEntry->EntryName, CurrentEntry->Data);
				}
				break;
			case EBlackboardKeyType::Float:
				{
					const UBlackboardConstantEntry_Float* CurrentEntry = Cast<UBlackboardConstantEntry_Float>(Entry);
					BlackboardComponent->SetValueAsFloat(CurrentEntry->EntryName, CurrentEntry->Data);
				}
				break;
			case EBlackboardKeyType::Int:
				{
					const UBlackboardConstantEntry_Int* CurrentEntry = Cast<UBlackboardConstantEntry_Int>(Entry);
					BlackboardComponent->SetValueAsInt(CurrentEntry->EntryName, CurrentEntry->Data);
				}
				break;
			case EBlackboardKeyType::Name:
				{
					const UBlackboardConstantEntry_Name* CurrentEntry = Cast<UBlackboardConstantEntry_Name>(Entry);
					BlackboardComponent->SetValueAsName(CurrentEntry->EntryName, CurrentEntry->Data);
				}
				break;
			case EBlackboardKeyType::Object:
				{
					const UBlackboardConstantEntry_Object* CurrentEntry = Cast<UBlackboardConstantEntry_Object>(Entry);
					BlackboardComponent->SetValueAsObject(CurrentEntry->EntryName, CurrentEntry->Data);
				}
				break;
			case EBlackboardKeyType::Rotator:
				{
					const UBlackboardConstantEntry_Rotator* CurrentEntry = Cast<UBlackboardConstantEntry_Rotator>(Entry);
					BlackboardComponent->SetValueAsRotator(CurrentEntry->EntryName, CurrentEntry->Data);
				}
				break;
			case EBlackboardKeyType::String:
				{
					const UBlackboardConstantEntry_String* CurrentEntry = Cast<UBlackboardConstantEntry_String>(Entry);
					BlackboardComponent->SetValueAsString(CurrentEntry->EntryName, CurrentEntry->Data);
				}
				break;
			case EBlackboardKeyType::Vector:
				{
					const UBlackboardConstantEntry_Vector* CurrentEntry = Cast<UBlackboardConstantEntry_Vector>(Entry);
					BlackboardComponent->SetValueAsVector(CurrentEntry->EntryName, CurrentEntry->Data);
				}
				break;
			default:
				check(false);
				break;
		}
	}
}

#if WITH_EDITOR
void UBlackboardConstant::UpdateConstantEntry()
{
	TArray<FBlackboardConstantGatherData> AllEntry;
	GatherAllEntry(AllEntry);
	
	TMap<FName, bool> ExistFlag;
	ValidateConstantEntry();
	for (const UBlackboardConstantEntry* Constant : ConstantEntry)
	{
		check(Constant != nullptr);
		ExistFlag.Add(Constant->EntryName, false);
	}
	
	for (const FBlackboardConstantGatherData& GatherData : AllEntry)
	{
		const FBlackboardEntry& Entry = GatherData.Entry;
		if (IsConstantEntry(Entry) == false)
		{
			continue;
		}
		
		UBlackboardConstantEntry** FoundEntry = ConstantEntry.FindByPredicate([&Entry](const UBlackboardConstantEntry* ConstEntry)
		{
			return Entry.EntryName == ConstEntry->EntryName;
		});

		if (FoundEntry == nullptr)
		{
			UBlackboardConstantEntry* NewConstEntry = MakeBlackboardConstantEntry(Entry.EntryName, Entry.KeyType, GatherData.bIsInherited, GatherData.Category);
			if (NewConstEntry != nullptr)
			{
				ConstantEntry.Add(NewConstEntry);
			}
		}
		else
		{
			ExistFlag.Add(Entry.EntryName, true);
			
			// Changed entry type
			EBlackboardKeyType KeyType = ConvertToEnumBlackboardKeyType(Entry.KeyType);
			if ((*FoundEntry)->BlackboardEntryType != KeyType)
			{
				(*FoundEntry)->BlackboardEntryType = KeyType;
				(*FoundEntry)->ClearData();
			}

			// Changed category
			(*FoundEntry)->Category = GatherData.Category;
		}
	}

	for (const TPair<FName, bool>& Flag : ExistFlag)
	{
		if (Flag.Value == false)
		{
			ConstantEntry.RemoveAll([&Flag](const UBlackboardConstantEntry* Entry)
			{
				return Entry->EntryName == Flag.Key;
			});
		}
	}

	SortConstantEntry();
}

UBlackboardConstantEntry* UBlackboardConstant::MakeBlackboardConstantEntry(const FName& InEntryName, UBlackboardKeyType* InKeyType, bool bIsInherit, const FText& InCategory)
{
	UBlackboardConstantEntry* OutEntry = nullptr;
	const EBlackboardKeyType KeyType = ConvertToEnumBlackboardKeyType(InKeyType);
	switch (KeyType)
	{
		case EBlackboardKeyType::Bool:
			OutEntry = NewObject<UBlackboardConstantEntry_Bool>(this);
			break;
		case EBlackboardKeyType::Class:
			OutEntry = NewObject<UBlackboardConstantEntry_Class>(this);
			break;
		case EBlackboardKeyType::Enum:
			OutEntry = NewObject<UBlackboardConstantEntry_Enum>(this);
			break;
		case EBlackboardKeyType::Float:
			OutEntry = NewObject<UBlackboardConstantEntry_Float>(this);
			break;
		case EBlackboardKeyType::Int:
			OutEntry = NewObject<UBlackboardConstantEntry_Int>(this);
			break;
		case EBlackboardKeyType::Name:
			OutEntry = NewObject<UBlackboardConstantEntry_Name>(this);
			break;
		case EBlackboardKeyType::Object:
			OutEntry = NewObject<UBlackboardConstantEntry_Object>(this);
			break;
		case EBlackboardKeyType::Rotator:
			OutEntry = NewObject<UBlackboardConstantEntry_Rotator>(this);
			break;
		case EBlackboardKeyType::String:
			OutEntry = NewObject<UBlackboardConstantEntry_String>(this);
			break;
		case EBlackboardKeyType::Vector:
			OutEntry = NewObject<UBlackboardConstantEntry_Vector>(this);
			break;
		default:
			check(false);
			break;
	}

	if (OutEntry != nullptr)
	{
		OutEntry->Initialize(InEntryName, KeyType, bIsInherit, InCategory);
	}

	return OutEntry;
}

void UBlackboardConstant::GatherAllEntry(TArray<FBlackboardConstantGatherData>& OutAllEntry)
{
	if (BlackboardData != nullptr)
	{
		OutAllEntry.Empty();
		BlackboardData->UpdateParentKeys();

		for (int32 Index = 0; Index < BlackboardData->ParentKeys.Num(); ++Index)
		{
			FBlackboardConstantGatherData GatherData;
			GatherData.Entry = BlackboardData->ParentKeys[Index];
			GatherData.bIsInherited = true;
			const FBlackboardEntryIdentifier Identifier(GatherData.Entry);
			if (BlackboardData->ParentCategories.Contains(Identifier))
			{
				GatherData.Category = *BlackboardData->ParentCategories.Find(Identifier);
			}
			OutAllEntry.Add(GatherData);
		}

		for (int32 Index = 0; Index < BlackboardData->Keys.Num(); ++Index)
		{
			FBlackboardConstantGatherData GatherData;
			GatherData.Entry = BlackboardData->Keys[Index];
			GatherData.bIsInherited = false;
			const FBlackboardEntryIdentifier Identifier(GatherData.Entry);
			if (BlackboardData->Categories.Contains(Identifier))
			{
				GatherData.Category = *BlackboardData->Categories.Find(Identifier);
			}
			OutAllEntry.Add(GatherData);
		}
	}
}

void UBlackboardConstant::ValidateConstantEntry()
{
	bool bIsValid = true;
	for (const UBlackboardConstantEntry* Entry : ConstantEntry)
	{
		if (Entry == nullptr)
		{
			bIsValid = false;
			break;
		}
	}

	if (bIsValid == false)
	{
		ConstantEntry.Empty();
	}
}

bool UBlackboardConstant::IsConstantEntry(const FBlackboardEntry& InEntry)
{
	bool bOutResult = false;
	if (BlackboardData != nullptr)
	{
		const FBlackboardEntryIdentifier Identifier(InEntry);
		if (BlackboardData->ParentConstantMap.Contains(Identifier))
		{
			bOutResult |= *BlackboardData->ParentConstantMap.Find(Identifier);
		}
		if (BlackboardData->ConstantMap.Contains(Identifier))
		{
			bOutResult |= *BlackboardData->ConstantMap.Find(Identifier);
		}
	}

	return bOutResult;
}

void UBlackboardConstant::SortConstantEntry()
{
	ConstantEntry.Sort([this](const UBlackboardConstantEntry& InA, const UBlackboardConstantEntry& InB)
	{
		if (InA.bIsInheritEntry != InB.bIsInheritEntry)
		{
			return InA.bIsInheritEntry ? false : true;
		}
		
		int32 IndexA = INDEX_NONE;
		int32 IndexB = INDEX_NONE;
		TArray<FBlackboardEntryIdentifier> CurrentOrder = InA.bIsInheritEntry ? BlackboardData->ParentKeysOrder : BlackboardData->KeysOrder;
		for (int32 Index = 0; Index < CurrentOrder.Num(); ++Index)
		{
			if (CurrentOrder[Index].EntryName == InA.EntryName)
			{
				IndexA = Index;
				break;
			}
		}
		for (int32 Index = 0; Index < CurrentOrder.Num(); ++Index)
		{
			if (CurrentOrder[Index].EntryName == InB.EntryName)
			{
				IndexB = Index;
				break;
			}
		}

		return IndexA < IndexB;
	});
}
#endif
