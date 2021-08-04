// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "BlackboardDataV2Factory.generated.h"

UCLASS()
class BLACKBOARDEXTENDEREDITOR_API UBlackboardDataV2Factory : public UFactory
{
	GENERATED_UCLASS_BODY()
	
	// Implementation UFactory interface
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool CanCreateNew() const override;

};
