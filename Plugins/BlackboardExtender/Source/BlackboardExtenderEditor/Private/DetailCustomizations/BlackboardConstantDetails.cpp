// Copyright RadTuna. All Rights Reserved.

// Primary Include
#include "BlackboardConstantDetails.h"

// Engine Include
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"


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
		IDetailCategoryBuilder& CategoryBuilder = DetailBuilder.EditCategory(TEXT("Constant"));

		for (UBlackboardConstantEntry* Entry : BlackboardConstant->ConstantEntry)
		{
			TArray<UObject*> PropertyEntry;
			PropertyEntry.Add(Entry);
			IDetailPropertyRow* PropertyRow = CategoryBuilder.AddExternalObjectProperty(PropertyEntry, TEXT("Data"));
			TSharedPtr<IPropertyHandle> PropertyHandle = PropertyRow->GetPropertyHandle();
			PropertyHandle->SetPropertyDisplayName(FText::FromName(Entry->EntryName));
		}
	}
}

