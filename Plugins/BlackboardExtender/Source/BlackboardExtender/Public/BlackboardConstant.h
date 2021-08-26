// Copyright RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "Engine/DataAsset.h"
#include "ConstantEntry/BlackboardConstantEntry.h"
#include "BlackboardConstant.generated.h"


USTRUCT()
struct FBlackboardConstantGatherData
{
	GENERATED_BODY()
	
	FBlackboardEntry Entry;
	bool bIsInherited;
	FText Category;
};

class UBEBlackboardData;

UCLASS(BlueprintType)
class BLACKBOARDEXTENDER_API UBlackboardConstant : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category=Blackboard)
	UBEBlackboardData* BlackboardData;

	UPROPERTY(EditAnywhere, Category=BlackboardConstant)
	TArray<UBlackboardConstantEntry*> ConstantEntry;

public:
	virtual void PostInitProperties() override;
	virtual void PostLoad() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UFUNCTION(BlueprintCallable, Category=BlackboardConstant)
	void InitBlackboardComponent(UBlackboardComponent* BlackboardComponent);
	
	void UpdateConstantEntry();
	UBlackboardConstantEntry* MakeBlackboardConstantEntry(const FName& InEntryName, UBlackboardKeyType* InKeyType, bool bIsInherit, const FText& InCategory);
	void GatherAllEntry(TArray<FBlackboardConstantGatherData>& OutAllEntry);
	void ValidateConstantEntry();
	bool IsConstantEntry(const FBlackboardEntry& InEntry);
	void SortConstantEntry();
	
};
