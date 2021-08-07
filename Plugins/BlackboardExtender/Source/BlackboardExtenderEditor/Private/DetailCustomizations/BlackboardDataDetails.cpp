// Copyright Epic Games, Inc. All Rights Reserved.

#include "DetailCustomizations/BlackboardDataDetails.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SBoxPanel.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "DetailCategoryBuilder.h"
#include "BehaviorTree/BlackboardData.h"
#include "BEBlackboardData.h"


#define LOCTEXT_NAMESPACE "BlackboardDataDetails"

TSharedRef<IDetailCustomization> FBlackboardDataDetails::MakeInstance(FOnGetSelectedBlackboardItemIndex InOnGetSelectedBlackboardItemIndex)
{
	return MakeShareable( new FBlackboardDataDetails(InOnGetSelectedBlackboardItemIndex) );
}

void FBlackboardDataDetails::CustomizeDetails( IDetailLayoutBuilder& DetailLayout )
{
	// First hide all keys
	//DetailLayout.HideCategory(TEXT("Blackboard"));
	DetailLayout.HideProperty(TEXT("Keys"));
	DetailLayout.HideProperty(TEXT("ParentKeys"));
	//DetailLayout.HideProperty(TEXT("Categories"));

	TArray<TWeakObjectPtr<UObject>> SelectedObjects = DetailLayout.GetSelectedObjects();
	if (SelectedObjects.Num() > 0)
	{
		UBlackboardData* BlackboardData = Cast<UBlackboardData>(SelectedObjects[0].Get());
		if (BlackboardData != nullptr)
		{
			BlackboardDataCached = BlackboardData;
		}
	}

	// Now show only the currently selected key
	bool bIsInherited = false;
	int32 CurrentSelection = INDEX_NONE;
	if(OnGetSelectedBlackboardItemIndex.IsBound())
	{
		CurrentSelection = OnGetSelectedBlackboardItemIndex.Execute(bIsInherited);
	}

	if(CurrentSelection >= 0)
	{
		TSharedPtr<IPropertyHandle> KeysHandle = bIsInherited ? DetailLayout.GetProperty(TEXT("ParentKeys")) : DetailLayout.GetProperty(TEXT("Keys"));
		check(KeysHandle.IsValid());
		uint32 NumChildKeys = 0;
		KeysHandle->GetNumChildren(NumChildKeys);
		if((uint32)CurrentSelection < NumChildKeys)
		{
			TSharedPtr<IPropertyHandle> KeyHandle = KeysHandle->GetChildHandle((uint32)CurrentSelection);

			IDetailCategoryBuilder& DetailCategoryBuilder = DetailLayout.EditCategory("Key");
			TSharedPtr<IPropertyHandle> EntryNameProperty = KeyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBlackboardEntry, EntryName));
			DetailCategoryBuilder.AddCustomRow(LOCTEXT("EntryNameLabel", "Entry Name"))
			.NameContent()
			[
				EntryNameProperty->CreatePropertyNameWidget()
			]
			.ValueContent()
			[
				SNew(SHorizontalBox)
				.IsEnabled(true)
				+SHorizontalBox::Slot()
				[
					EntryNameProperty->CreatePropertyValueWidget()
				]
			];

#if WITH_EDITORONLY_DATA
// 			TSharedPtr<IPropertyHandle> EntryDescriptionHandle = ElementProperty->GetChildHandle("EntryDescription");
			TSharedPtr<IPropertyHandle> EntryDescriptionHandle = KeyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBlackboardEntry, EntryDescription));

			DetailCategoryBuilder.AddProperty(EntryDescriptionHandle);

			UBEBlackboardData* BEBlackboardData = Cast<UBEBlackboardData>(BlackboardDataCached.Get());
			if (BEBlackboardData != nullptr)
			{
				const TArray<FBlackboardEntry>& CurrentEntryArray = bIsInherited ? BEBlackboardData->ParentKeys : BEBlackboardData->Keys;
				const FBlackboardEntry& CurrentEntry = CurrentEntryArray[CurrentSelection];
				const FBlackboardEntryIdentifier Identifier(CurrentEntry);
				const FText* CurrentCategory = nullptr;
				if (BEBlackboardData->Categories.Contains(Identifier))
				{
					CurrentCategory = BEBlackboardData->Categories.Find(Identifier);
				}

				if (CurrentCategory != nullptr)
				{
					FSlateFontInfo FontStyle = FEditorStyle::GetFontStyle(TEXT("PropertyWindow.NormalFont"));
					const FText CategoryRowName = LOCTEXT("EntryCategory", "Category");
					DetailCategoryBuilder.AddCustomRow(CategoryRowName)
					.NameContent()
					[
						SNew(STextBlock)
						.SimpleTextMode(true)
						.Font(FontStyle)
						.Text(CategoryRowName)
					]
					.ValueContent()
					[
						SNew(SHorizontalBox)
						+SHorizontalBox::Slot()
						.FillWidth(1.0f)
						[
							SNew(SEditableTextBox)
							.Text(*CurrentCategory)
							.Font(FontStyle)
							.SelectAllTextWhenFocused(true)
							.ClearKeyboardFocusOnCommit(false)
							//.OnTextCommitted( this, &SPropertyEditorText::OnTextCommitted )
							.SelectAllTextOnCommit(true)
							.IsReadOnly(false)
						]
					];
				}
			}
#endif

			TSharedPtr<IPropertyHandle> KeyTypeProperty = KeyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBlackboardEntry, KeyType));
			DetailCategoryBuilder.AddProperty(KeyTypeProperty);

			TSharedPtr<IPropertyHandle> bInstanceSyncedProperty = KeyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBlackboardEntry, bInstanceSynced));
			DetailCategoryBuilder.AddProperty(bInstanceSyncedProperty);
		}	
	}
}

#undef LOCTEXT_NAMESPACE
