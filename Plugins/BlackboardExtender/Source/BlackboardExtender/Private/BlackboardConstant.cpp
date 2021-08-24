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
	for (const UBlackboardConstantEntry* Constant : ConstantEntry)
	{
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
	if (InKeyType->IsA(UBlackboardKeyType_Bool::StaticClass()))
	{
		return NewObject<UBlackboardConstantEntry_Bool>();
	}
	else if (InKeyType->IsA(UBlackboardKeyType_Class::StaticClass()))
	{
		return NewObject<UBlackboardConstantEntry_Class>();
	}
	else if (InKeyType->IsA(UBlackboardKeyType_Enum::StaticClass()) || InKeyType->IsA(UBlackboardKeyType_NativeEnum::StaticClass()))
	{
		return NewObject<UBlackboardConstantEntry_Enum>();
	}
	else if (InKeyType->IsA(UBlackboardKeyType_Float::StaticClass()))
	{
		return NewObject<UBlackboardConstantEntry_Float>();
	}
	else if (InKeyType->IsA(UBlackboardKeyType_Int::StaticClass()))
	{
		return NewObject<UBlackboardConstantEntry_Int>();
	}
	else if (InKeyType->IsA(UBlackboardKeyType_Name::StaticClass()))
	{
		return NewObject<UBlackboardConstantEntry_Name>();
	}
	else if (InKeyType->IsA(UBlackboardKeyType_Object::StaticClass()))
	{
		return NewObject<UBlackboardConstantEntry_Object>();
	}
	else if (InKeyType->IsA(UBlackboardKeyType_Rotator::StaticClass()))
	{
		return NewObject<UBlackboardConstantEntry_Rotator>();
	}
	else if (InKeyType->IsA(UBlackboardKeyType_String::StaticClass()))
	{
		return NewObject<UBlackboardConstantEntry_String>();
	}
	else if (InKeyType->IsA(UBlackboardKeyType_Vector::StaticClass()))
	{
		return NewObject<UBlackboardConstantEntry_Vector>();
	}

	return nullptr;
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
