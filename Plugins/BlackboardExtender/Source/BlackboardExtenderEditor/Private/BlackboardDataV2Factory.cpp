// Fill out your copyright notice in the Description page of Project Settings.

// Primary Include
#include "BlackboardDataV2Factory.h"

// User Include
#include "BEBlackboardData.h"

UBlackboardDataV2Factory::UBlackboardDataV2Factory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UBEBlackboardData::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UBlackboardDataV2Factory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	check(InClass->IsChildOf(UBEBlackboardData::StaticClass()));
	return NewObject<UBEBlackboardData>(InParent, InClass, InName, Flags);
}

bool UBlackboardDataV2Factory::CanCreateNew() const
{
	return true;
}
