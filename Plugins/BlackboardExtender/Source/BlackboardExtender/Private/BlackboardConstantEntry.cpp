// Copyright 2021 RadTuna. All Rights Reserved.

// Primary Include
#include "ConstantEntry/BlackboardConstantEntry.h"

// User Include
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


EBlackboardKeyType ConvertToEnumBlackboardKeyType(UBlackboardKeyType* InKeyType)
{
	EBlackboardKeyType OutType = EBlackboardKeyType::Unknown;
	if (InKeyType->IsA(UBlackboardKeyType_Bool::StaticClass()))
	{
		OutType = EBlackboardKeyType::Bool;
	}
	else if (InKeyType->IsA(UBlackboardKeyType_Class::StaticClass()))
	{
		OutType = EBlackboardKeyType::Class;
	}
	else if (InKeyType->IsA(UBlackboardKeyType_Enum::StaticClass()) || InKeyType->IsA(UBlackboardKeyType_NativeEnum::StaticClass()))
	{
		OutType = EBlackboardKeyType::Enum;
	}
	else if (InKeyType->IsA(UBlackboardKeyType_Float::StaticClass()))
	{
		OutType = EBlackboardKeyType::Float;
	}
	else if (InKeyType->IsA(UBlackboardKeyType_Int::StaticClass()))
	{
		OutType = EBlackboardKeyType::Int;
	}
	else if (InKeyType->IsA(UBlackboardKeyType_Name::StaticClass()))
	{
		OutType = EBlackboardKeyType::Name;
	}
	else if (InKeyType->IsA(UBlackboardKeyType_Object::StaticClass()))
	{
		OutType = EBlackboardKeyType::Object;
	}
	else if (InKeyType->IsA(UBlackboardKeyType_Rotator::StaticClass()))
	{
		OutType = EBlackboardKeyType::Rotator;
	}
	else if (InKeyType->IsA(UBlackboardKeyType_String::StaticClass()))
	{
		OutType = EBlackboardKeyType::String;
	}
	else if (InKeyType->IsA(UBlackboardKeyType_Vector::StaticClass()))
	{
		OutType = EBlackboardKeyType::Vector;
	}

	return OutType;
}
