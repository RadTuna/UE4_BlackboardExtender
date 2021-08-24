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
	
	FSlateFontInfo FontStyle = FEditorStyle::GetFontStyle(TEXT("PropertyWindow.NormalFont"));
	IDetailCategoryBuilder& CategoryBuilder = DetailBuilder.EditCategory(TEXT("Constant"));

	TSharedPtr<IPropertyHandle> ConstantHandle = DetailBuilder.GetProperty(TEXT("ConstantEntry"));
	for (int32 Index = 0; Index < BlackboardConstant->ConstantEntry.Num(); ++Index)
	{
		const UBlackboardConstantEntry* Entry = BlackboardConstant->ConstantEntry[Index];
		TSharedPtr<IPropertyHandle> EntryHandle = ConstantHandle->GetChildHandle(static_cast<uint32>(Index));
		TSharedPtr<IPropertyHandle> DataHandle = EntryHandle->GetChildHandle(TEXT("Data"));
		
		const FText RowName = FText::FromName(Entry->EntryName);
		CategoryBuilder.AddCustomRow(RowName)
		.NameContent()
		[
			SNew(STextBlock)
			.SimpleTextMode(true)
			.Font(FontStyle)
			.Text(RowName)
		]
		.ValueContent()
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			[
				DataHandle->CreatePropertyValueWidget()
			]
		];
	}
}

