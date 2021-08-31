// Copyright 2021 RadTuna. All Rights Reserved.

// Primary Include
#include "BlackboardConstantDetails.h"

// Engine Include
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailGroup.h"


void FConstantCategoryNode::AddCategory(const TArray<FName>& InCategoryArray, UBlackboardConstantEntry* Entry)
{
	const FName& FirstCategory = InCategoryArray[0];
	if (CategoryName == FirstCategory)
	{
		TArray<FName> SubCategoryArray = InCategoryArray;
		SubCategoryArray.RemoveAt(0);

		if (SubCategoryArray.Num() > 0)
		{
			const FName& SecondCategory = SubCategoryArray[0];
			for (const TSharedPtr<FConstantCategoryNode>& Node : ChildCategory)
			{
				if (Node->CategoryName == SecondCategory)
				{
					if (SubCategoryArray.Num() > 0)
					{
						Node->AddCategory(SubCategoryArray, Entry);
					}
					else
					{
						Entries.Add(Entry);
					}
					return;
				}
			}

			TSharedPtr<FConstantCategoryNode> NewNode = MakeShareable(new FConstantCategoryNode(SecondCategory));
			ChildCategory.Add(NewNode);
			NewNode->AddCategory(SubCategoryArray, Entry);
		}
		else
		{
			Entries.Add(Entry);
		}
	}
}

void FConstantCategoryNode::AddCategory(const TArray<FString>& InCategoryArray, UBlackboardConstantEntry* Entry)
{
	TArray<FName> NameCategoryArray;
	for (const FString& Category : InCategoryArray)
	{
		NameCategoryArray.Add(FName(*Category));
	}
	AddCategory(NameCategoryArray, Entry);
}

void FConstantCategoryNode::ApplyCategoryGroup(IDetailCategoryBuilder& CategoryBuilder)
{
	if (CategoryName != NAME_None)
	{
		IDetailGroup& CurrentGroup = CategoryBuilder.AddGroup(CategoryName, FText::FromName(CategoryName));
		for (TSharedPtr<FConstantCategoryNode>& Node : ChildCategory)
		{
			Node->ApplyCategoryGroup(CategoryBuilder, CurrentGroup);
		}

		for (UBlackboardConstantEntry* Entry : Entries)
		{
			TSharedPtr<IPropertyHandle> PropertyHandle = GetPropertyHandle(CategoryBuilder, Entry);
			CurrentGroup.AddPropertyRow(PropertyHandle.ToSharedRef());
		}
	}
	else
	{
		for (UBlackboardConstantEntry* Entry : Entries)
		{
			TSharedPtr<IPropertyHandle> PropertyHandle = GetPropertyHandle(CategoryBuilder, Entry);
			CategoryBuilder.AddProperty(PropertyHandle.ToSharedRef());
		}
	}
}

void FConstantCategoryNode::ApplyCategoryGroup(IDetailCategoryBuilder& CategoryBuilder, IDetailGroup& Group)
{
	IDetailGroup& CurrentGroup = Group.AddGroup(CategoryName, FText::FromName(CategoryName));
	for (TSharedPtr<FConstantCategoryNode>& Node : ChildCategory)
	{
		Node->ApplyCategoryGroup(CategoryBuilder, CurrentGroup);
	}

	for (UBlackboardConstantEntry* Entry : Entries)
	{
		TSharedPtr<IPropertyHandle> PropertyHandle = GetPropertyHandle(CategoryBuilder, Entry);
		CurrentGroup.AddPropertyRow(PropertyHandle.ToSharedRef());
	}
}

TSharedPtr<IPropertyHandle> FConstantCategoryNode::GetPropertyHandle(IDetailCategoryBuilder& CategoryBuilder, UBlackboardConstantEntry* Entry)
{
	TArray<UObject*> PropertyEntry;
	PropertyEntry.Add(Entry);
	IDetailPropertyRow* PropertyRow = CategoryBuilder.AddExternalObjectProperty(PropertyEntry, TEXT("Data"));
	PropertyRow->Visibility(EVisibility::Hidden);
			
	TSharedPtr<IPropertyHandle> PropertyHandle = PropertyRow->GetPropertyHandle();
	PropertyHandle->SetPropertyDisplayName(FText::FromName(Entry->EntryName));
	return PropertyHandle;
}

FBlackboardConstantDetails::FBlackboardConstantDetails()
{
}

TSharedRef<IDetailCustomization> FBlackboardConstantDetails::MakeInstance()
{
	return MakeShareable(new FBlackboardConstantDetails());
}

void FBlackboardConstantDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	// Hide all properties;
	DetailBuilder.HideCategory(TEXT("BlackboardConstant"));

	TArray<TWeakObjectPtr<UObject>> SelectedObjects = DetailBuilder.GetSelectedObjects();
	if (SelectedObjects.Num() > 0)
	{
		UBlackboardConstant* BlackboardConstant = Cast<UBlackboardConstant>(SelectedObjects[0].Get());
		if (BlackboardConstant != nullptr)
		{
			BlackboardConstantCached = BlackboardConstant;
		}
	}
	
	UBlackboardConstant* BlackboardConstant = BlackboardConstantCached.Get();
	if (BlackboardConstant != nullptr)
	{
		TArray<TSharedPtr<FConstantCategoryNode>> CategoryNodes;
		for (UBlackboardConstantEntry* Entry : BlackboardConstant->ConstantEntry)
		{
			TArray<FString> Tokens;
			Entry->Category.ToString().ParseIntoArray(Tokens, TEXT("|"), true);
			if (Tokens.Num() <= 0)
			{
				Tokens.Add(TEXT(""));
			}

			const FName CategoryName(*Tokens[0]);
			bool bIsAdded = false;
			for (TSharedPtr<FConstantCategoryNode>& Node : CategoryNodes)
			{
				if (Node->GetCategoryName() == CategoryName)
				{
					Node->AddCategory(Tokens, Entry);
					bIsAdded = true;
				}
			}

			if (bIsAdded == false)
			{
				TSharedPtr<FConstantCategoryNode> NewNode = MakeShareable(new FConstantCategoryNode(CategoryName));
				CategoryNodes.Add(NewNode);
				NewNode->AddCategory(Tokens, Entry);
			}
		}

		IDetailCategoryBuilder& CategoryBuilder = DetailBuilder.EditCategory(TEXT("Constant"));
		for (TSharedPtr<FConstantCategoryNode>& Node : CategoryNodes)
		{
			Node->ApplyCategoryGroup(CategoryBuilder);
		}
	}
}

