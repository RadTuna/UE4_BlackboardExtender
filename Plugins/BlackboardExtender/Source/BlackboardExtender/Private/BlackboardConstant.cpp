// Copyright RadTuna. All Rights Reserved.

// Primary Include
#include "BlackboardConstant.h"

// Engine Include
#include "BEBlackboardData.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Class.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Name.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_NativeEnum.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Rotator.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_String.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

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

	TArray<FBlackboardEntry> AllEntry;
	GatherAllEntry(AllEntry);
	UpdateConstantEntry(AllEntry);
}

void UBlackboardConstant::PostLoad()
{
	Super::PostLoad();

	TArray<FBlackboardEntry> AllEntry;
	GatherAllEntry(AllEntry);
	UpdateConstantEntry(AllEntry);
}

#if WITH_EDITOR
void UBlackboardConstant::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	TArray<FBlackboardEntry> AllEntry;
	GatherAllEntry(AllEntry);
	UpdateConstantEntry(AllEntry);
}
#endif

void UBlackboardConstant::UpdateConstantEntry(const TArray<FBlackboardEntry>& AllEntry)
{
	TMap<FName, bool> ExistFlag;
	ValidateConstantEntry();
	for (const UBlackboardConstantEntry* Constant : ConstantEntry)
	{
		check(Constant != nullptr);
		ExistFlag.Add(Constant->EntryName, false);
	}
	
	for (const FBlackboardEntry& Entry : AllEntry)
	{
		UBlackboardConstantEntry** FoundEntry = ConstantEntry.FindByPredicate([&Entry](const UBlackboardConstantEntry* ConstEntry)
		{
			return Entry.EntryName == ConstEntry->EntryName;
		});

		if (FoundEntry == nullptr)
		{
			UBlackboardConstantEntry* NewConstEntry = MakeBlackboardConstantEntry(Entry.EntryName, Entry.KeyType);
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
}

UBlackboardConstantEntry* UBlackboardConstant::MakeBlackboardConstantEntry(const FName& InEntryName, UBlackboardKeyType* InKeyType)
{
	UBlackboardConstantEntry* OutEntry = nullptr;
	EBlackboardKeyType KeyType = ConvertToEnumBlackboardKeyType(InKeyType);
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
	}

	if (OutEntry != nullptr)
	{
		OutEntry->EntryName = InEntryName;
		OutEntry->BlackboardEntryType = KeyType;
	}

	return OutEntry;
}

void UBlackboardConstant::GatherAllEntry(TArray<FBlackboardEntry>& OutAllEntry)
{
	if (BlackboardData != nullptr)
	{
		OutAllEntry.Empty();
		BlackboardData->UpdateParentKeys();
		OutAllEntry.Append(BlackboardData->ParentKeys);
		OutAllEntry.Append(BlackboardData->Keys);
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
