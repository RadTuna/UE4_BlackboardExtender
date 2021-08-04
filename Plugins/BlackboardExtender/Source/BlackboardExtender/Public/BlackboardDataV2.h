﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BlackboardData.h"
#include "BlackboardDataV2.generated.h"


UCLASS()
class BLACKBOARDEXTENDER_API UBlackboardDataV2 : public UBlackboardData
{
	GENERATED_UCLASS_BODY()

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category=Blackboard)
	TArray<FText> Categories;
#endif
};
