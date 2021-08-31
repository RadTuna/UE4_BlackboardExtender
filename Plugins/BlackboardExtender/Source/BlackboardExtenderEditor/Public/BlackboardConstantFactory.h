// Copyright 2021 RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "BlackboardConstantFactory.generated.h"


UCLASS()
class BLACKBOARDEXTENDEREDITOR_API UBlackboardConstantFactory : public UFactory
{
	GENERATED_UCLASS_BODY()

	// Implementation UFactory interface
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool CanCreateNew() const override;
	
};
