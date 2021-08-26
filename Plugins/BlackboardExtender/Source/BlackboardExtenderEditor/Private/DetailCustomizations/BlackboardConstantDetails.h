// Copyright RadTuna. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BlackboardConstant.h"
#include "DetailCategoryBuilder.h"
#include "IDetailCustomization.h"


class FConstantCategoryNode : public TSharedFromThis<FConstantCategoryNode>
{
public:
	FConstantCategoryNode(const FName& InCategoryName)
		: CategoryName(InCategoryName)
	{
	}
	~FConstantCategoryNode() {}

	void AddCategory(const TArray<FName>& InCategoryArray, UBlackboardConstantEntry* Entry);
	void AddCategory(const TArray<FString>& InCategoryArray, UBlackboardConstantEntry* Entry);
	const FName& GetCategoryName() const { return CategoryName; }

	void ApplyCategoryGroup(IDetailCategoryBuilder& CategoryBuilder);
	void ApplyCategoryGroup(IDetailCategoryBuilder& CategoryBuilder, IDetailGroup& Group);
	TSharedPtr<IPropertyHandle> GetPropertyHandle(IDetailCategoryBuilder& CategoryBuilder, UBlackboardConstantEntry* Entry);

private:
	FName CategoryName;
	TArray<UBlackboardConstantEntry*> Entries;
	
	TArray<TSharedPtr<FConstantCategoryNode>> ChildCategory;
};

class FBlackboardConstantDetails : public IDetailCustomization
{
public:
	FBlackboardConstantDetails();

	static TSharedRef<IDetailCustomization> MakeInstance();

	// IDetailCustomization interface
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	TWeakObjectPtr<UBlackboardConstant> BlackboardConstantCached;
	
};
