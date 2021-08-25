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
			if ((*FoundEntry)->BlackboardEntryType != Entry.KeyType)
			{
				(*FoundEntry)->BlackboardEntryType = Entry.KeyType;
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
	if (InKeyType->IsA(UBlackboardKeyType_Bool::StaticClass()))
	{
		OutEntry = NewObject<UBlackboardConstantEntry_Bool>(this);
	}
	else if (InKeyType->IsA(UBlackboardKeyType_Class::StaticClass()))
	{
		OutEntry = NewObject<UBlackboardConstantEntry_Class>(this);
	}
	else if (InKeyType->IsA(UBlackboardKeyType_Enum::StaticClass()) || InKeyType->IsA(UBlackboardKeyType_NativeEnum::StaticClass()))
	{
		OutEntry = NewObject<UBlackboardConstantEntry_Enum>(this);
	}
	else if (InKeyType->IsA(UBlackboardKeyType_Float::StaticClass()))
	{
		OutEntry = NewObject<UBlackboardConstantEntry_Float>(this);
	}
	else if (InKeyType->IsA(UBlackboardKeyType_Int::StaticClass()))
	{
		OutEntry = NewObject<UBlackboardConstantEntry_Int>(this);
	}
	else if (InKeyType->IsA(UBlackboardKeyType_Name::StaticClass()))
	{
		OutEntry = NewObject<UBlackboardConstantEntry_Name>(this);
	}
	else if (InKeyType->IsA(UBlackboardKeyType_Object::StaticClass()))
	{
		OutEntry = NewObject<UBlackboardConstantEntry_Object>(this);
	}
	else if (InKeyType->IsA(UBlackboardKeyType_Rotator::StaticClass()))
	{
		OutEntry = NewObject<UBlackboardConstantEntry_Rotator>(this);
	}
	else if (InKeyType->IsA(UBlackboardKeyType_String::StaticClass()))
	{
		OutEntry = NewObject<UBlackboardConstantEntry_String>(this);
	}
	else if (InKeyType->IsA(UBlackboardKeyType_Vector::StaticClass()))
	{
		OutEntry = NewObject<UBlackboardConstantEntry_Vector>(this);
	}

	if (OutEntry != nullptr)
	{
		OutEntry->EntryName = InEntryName;
		OutEntry->BlackboardEntryType = InKeyType;
	}

	return OutEntry;
}

void UBlackboardConstant::GatherAllEntry(TArray<FBlackboardEntry>& OutAllEntry)
{
	if (BlackboardData != nullptr)
	{
		OutAllEntry.Empty();
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
