// Copyright 2021 RadTuna. All Rights Reserved.

// Primary Include
#include "BlackboardConstantFactory.h"

// User Include
#include "BlackboardConstant.h"


UBlackboardConstantFactory::UBlackboardConstantFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UBlackboardConstant::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UBlackboardConstantFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	check(InClass->IsChildOf(UBlackboardConstant::StaticClass()));
	return NewObject<UBlackboardConstant>(InParent, InClass, InName, Flags);
}

bool UBlackboardConstantFactory::CanCreateNew() const
{
	return true;
}
