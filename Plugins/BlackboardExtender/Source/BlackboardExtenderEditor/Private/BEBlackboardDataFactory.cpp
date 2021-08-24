// Fill out your copyright notice in the Description page of Project Settings.

// Primary Include
#include "BEBlackboardDataFactory.h"

// User Include
#include "BEBlackboardData.h"


UBEBlackboardDataFactory::UBEBlackboardDataFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UBEBlackboardData::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UBEBlackboardDataFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	check(InClass->IsChildOf(UBEBlackboardData::StaticClass()));
	return NewObject<UBEBlackboardData>(InParent, InClass, InName, Flags);
}

bool UBEBlackboardDataFactory::CanCreateNew() const
{
	return true;
}
