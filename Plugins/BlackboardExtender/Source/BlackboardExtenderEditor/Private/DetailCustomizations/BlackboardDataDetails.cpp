// Copyright 2021 RadTuna. All Rights Reserved.

#include "DetailCustomizations/BlackboardDataDetails.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SBoxPanel.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "DetailCategoryBuilder.h"
#include "BehaviorTree/BlackboardData.h"
#include "BEBlackboardData.h"
#include "SBehaviorTreeBlackboardView.h"


#define LOCTEXT_NAMESPACE "BlackboardDataDetails"

TSharedRef<IDetailCustomization> FBlackboardDataDetails::MakeInstance(TWeakPtr<SBehaviorTreeBlackboardView> InBlackboardView, FOnGetSelectedBlackboardItemIndex InOnGetSelectedBlackboardItemIndex)
{
	return MakeShareable( new FBlackboardDataDetails(InBlackboardView, InOnGetSelectedBlackboardItemIndex) );
}

void FBlackboardDataDetails::CustomizeDetails( IDetailLayoutBuilder& DetailLayout )
{
	// First hide all keys
	DetailLayout.HideCategory(TEXT("BlackboardCategory"));
	DetailLayout.HideProperty(TEXT("Keys"));
	DetailLayout.HideProperty(TEXT("ParentKeys"));

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

	CurrentCategorySelection = CurrentSelection;
	bIsInheritedSelection = bIsInherited;

	if(CurrentSelection >= 0)
	{
		TSharedPtr<IPropertyHandle> KeysHandle = bIsInherited ? DetailLayout.GetProperty(TEXT("ParentKeys")) : DetailLayout.GetProperty(TEXT("Keys"));
		check(KeysHandle.IsValid());
		KeysPropertyHandleCached = KeysHandle;
		uint32 NumChildKeys = 0;
		KeysHandle->GetNumChildren(NumChildKeys);
		if((uint32)CurrentSelection < NumChildKeys)
		{
			TSharedPtr<IPropertyHandle> KeyHandle = KeysHandle->GetChildHandle((uint32)CurrentSelection);

			IDetailCategoryBuilder& DetailCategoryBuilder = DetailLayout.EditCategory("Key");
			TSharedPtr<IPropertyHandle> EntryNameProperty = KeyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBlackboardEntry, EntryName));

			FSlateFontInfo FontStyle = FEditorStyle::GetFontStyle(TEXT("PropertyWindow.NormalFont"));
			const TArray<FBlackboardEntry>& CurrentEntryArray = bIsInherited ? BlackboardDataCached->ParentKeys : BlackboardDataCached->Keys;
			const FBlackboardEntry& CurrentEntry = CurrentEntryArray[CurrentSelection];
			
			DetailCategoryBuilder.AddCustomRow(LOCTEXT("EntryNameLabel", "Entry Name"))
			.NameContent()
			[
				EntryNameProperty->CreatePropertyNameWidget()
			]
			.ValueContent()
			[
				SNew(SHorizontalBox)
				.IsEnabled(!bIsInherited)
				+SHorizontalBox::Slot()
				[
					//EntryNameProperty->CreatePropertyValueWidget()
					SNew(SEditableTextBox)
					.Text(FText::FromName(CurrentEntry.EntryName))
					.Font(FontStyle)
					.SelectAllTextWhenFocused(true)
					.ClearKeyboardFocusOnCommit(false)
					.OnTextCommitted(this, &FBlackboardDataDetails::HandleOnCommittedEntryName)
					.OnVerifyTextChanged(this, &FBlackboardDataDetails::HandleOnVerifyEntryNameChanged)
					.SelectAllTextOnCommit(true)
					.IsReadOnly(false)
				]
			];

#if WITH_EDITORONLY_DATA
// 			TSharedPtr<IPropertyHandle> EntryDescriptionHandle = ElementProperty->GetChildHandle("EntryDescription");
			TSharedPtr<IPropertyHandle> EntryDescriptionHandle = KeyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBlackboardEntry, EntryDescription));
			
			DetailCategoryBuilder.AddProperty(EntryDescriptionHandle);

			UBEBlackboardData* BEBlackboardData = Cast<UBEBlackboardData>(BlackboardDataCached.Get());
			if (BEBlackboardData != nullptr)
			{
				const FBlackboardEntryIdentifier Identifier(CurrentEntry);
				const FText CurrentCategory = BEBlackboardData->GetUniqueCategory(Identifier, bIsInherited);
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
					.IsEnabled(!bIsInherited)
					+SHorizontalBox::Slot()
					.FillWidth(1.0f)
					[
						SNew(SEditableTextBox)
						.Text(CurrentCategory)
						.Font(FontStyle)
						.SelectAllTextWhenFocused(true)
						.ClearKeyboardFocusOnCommit(false)
						.OnTextCommitted(this, &FBlackboardDataDetails::HandleOnCommittedCategory)
						.SelectAllTextOnCommit(true)
						.IsReadOnly(false)
					]
				];
			}
#endif

			TSharedPtr<IPropertyHandle> KeyTypeProperty = KeyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBlackboardEntry, KeyType));
			DetailCategoryBuilder.AddProperty(KeyTypeProperty);

			TSharedPtr<IPropertyHandle> bInstanceSyncedProperty = KeyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBlackboardEntry, bInstanceSynced));
			DetailCategoryBuilder.AddProperty(bInstanceSyncedProperty);

			const FText ConstantRowName = LOCTEXT("EntryConstant", "Is Constant");
			DetailCategoryBuilder.AddCustomRow(ConstantRowName)
			.NameContent()
			[
				SNew(STextBlock)
				.SimpleTextMode(true)
				.Font(FontStyle)
				.Text(ConstantRowName)
			]
			.ValueContent()
			[
				SNew(SHorizontalBox)
				.IsEnabled(!bIsInherited)
				+SHorizontalBox::Slot()
				.FillWidth(1.0f)
				[
					SNew(SCheckBox)
					.IsChecked(this, &FBlackboardDataDetails::HandleOnIsConstantChecked)
					.OnCheckStateChanged(this, &FBlackboardDataDetails::HandleOnConstantCheckStateChanged)
				]
			];
			
		}	
	}
}

void FBlackboardDataDetails::HandleOnCommittedEntryName(const FText& InName, ETextCommit::Type CommitType)
{
	if (!KeysPropertyHandleCached.IsValid())
	{
		return;
	}

	check(BlackboardDataCached != nullptr);
	if (CurrentCategorySelection < 0)
	{
		return;
	}
	
	TArray<FBlackboardEntry>& CurrentEntryArray = bIsInheritedSelection ? BlackboardDataCached->ParentKeys : BlackboardDataCached->Keys;
	FBlackboardEntry& CurrentEntry = CurrentEntryArray[CurrentCategorySelection];
	const FBlackboardEntryIdentifier OldIdentifier(CurrentEntry);

	UBEBlackboardData* BEBlackboardData = Cast<UBEBlackboardData>(BlackboardDataCached.Get());
	if (BEBlackboardData != nullptr)
	{
		BEBlackboardData->SetEntryName(CurrentEntry.EntryName, FName(*InName.ToString()), bIsInheritedSelection);
	}

	TSharedPtr<IPropertyHandle> KeyHandle = KeysPropertyHandleCached->GetChildHandle(static_cast<uint32>(CurrentCategorySelection));
	TSharedPtr<IPropertyHandle> EntryNameProperty = KeyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FBlackboardEntry, EntryName));

	PostEditBlackboardProperty();
}

bool FBlackboardDataDetails::HandleOnVerifyEntryNameChanged(const FText& InNewText, FText& OutErrorMessage)
{
	check(BlackboardDataCached != nullptr);
	if (CurrentCategorySelection < 0)
	{
		OutErrorMessage = FText::GetEmpty();
		return false;
	}

	TArray<FBlackboardEntry>& CurrentEntryArray = bIsInheritedSelection ? BlackboardDataCached->ParentKeys : BlackboardDataCached->Keys;
	const FBlackboardEntry& CurrentEntry = CurrentEntryArray[CurrentCategorySelection];
	const FBlackboardEntryIdentifier Identifier(CurrentEntry);

	UBlackboardData* BlackboardData = BlackboardDataCached.Get();
	if (BlackboardData != nullptr)
	{
		for (const FBlackboardEntry& ParentEntry : BlackboardData->ParentKeys)
		{
			if (ParentEntry.EntryName == FName(*InNewText.ToString()))
			{
				OutErrorMessage = LOCTEXT("ParentBlackboardEntryErrorMessage", "Duplicate name in Parent Blackboard Entry.");
				return false;
			}
		}
		for (const FBlackboardEntry& Entry : BlackboardData->Keys)
		{
			if (Entry.EntryName == FName(*InNewText.ToString()))
			{
				OutErrorMessage = LOCTEXT("BlackboardEntryErrorMessage", "Duplicate name in Blackboard Entry.");
				return false;
			}
		}
	}

	return true;
}

void FBlackboardDataDetails::HandleOnCommittedCategory(const FText& InCategory, ETextCommit::Type CommitType)
{
	if (!KeysPropertyHandleCached.IsValid())
	{
		return;
	}
	
	UBEBlackboardData* BEBlackboardData = Cast<UBEBlackboardData>(BlackboardDataCached.Get());
	check(BEBlackboardData != nullptr);
	
	if (CurrentCategorySelection < 0)
	{
		return;
	}
	
	const TArray<FBlackboardEntry>& CurrentEntryArray = bIsInheritedSelection ? BEBlackboardData->ParentKeys : BEBlackboardData->Keys;
	const FBlackboardEntry& CurrentEntry = CurrentEntryArray[CurrentCategorySelection];
	const FBlackboardEntryIdentifier Identifier(CurrentEntry);
	BEBlackboardData->AddUniqueCategory(Identifier, InCategory, bIsInheritedSelection);

	PostEditBlackboardProperty();
}

ECheckBoxState FBlackboardDataDetails::HandleOnIsConstantChecked() const
{
	ECheckBoxState OutState = ECheckBoxState::Undetermined;
	UBEBlackboardData* BEBlackboardData = Cast<UBEBlackboardData>(BlackboardDataCached);
	if (BEBlackboardData != nullptr && CurrentCategorySelection >= 0)
	{
		TArray<FBlackboardEntry>& CurrentEntryArray = bIsInheritedSelection ? BlackboardDataCached->ParentKeys : BlackboardDataCached->Keys;
		const FBlackboardEntry& CurrentEntry = CurrentEntryArray[CurrentCategorySelection];
		const FBlackboardEntryIdentifier Identifier(CurrentEntry);

		const bool* Result = BEBlackboardData->GetUniqueConstant(Identifier, bIsInheritedSelection);
		if (Result != nullptr)
		{
			OutState = *Result ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
		}
	}

	return OutState;
}

void FBlackboardDataDetails::HandleOnConstantCheckStateChanged(ECheckBoxState InCheckState)
{
	UBEBlackboardData* BEBlackboardData = Cast<UBEBlackboardData>(BlackboardDataCached);
	if (BEBlackboardData != nullptr && CurrentCategorySelection >= 0)
	{
		TArray<FBlackboardEntry>& CurrentEntryArray = bIsInheritedSelection ? BlackboardDataCached->ParentKeys : BlackboardDataCached->Keys;
		const FBlackboardEntry& CurrentEntry = CurrentEntryArray[CurrentCategorySelection];
		const FBlackboardEntryIdentifier Identifier(CurrentEntry);

		if (BEBlackboardData->GetUniqueConstant(Identifier, bIsInheritedSelection) != nullptr)
		{
			bool CheckData = false;
			switch (InCheckState)
			{
				case ECheckBoxState::Checked:
					CheckData = true;
					break;
				case ECheckBoxState::Unchecked:
					CheckData = false;
					break;
				default:
					check(false);
					break;
			}
			
			BEBlackboardData->SetUniqueConstant(Identifier, CheckData, bIsInheritedSelection);

			PostEditBlackboardProperty();
		}
	}
}

void FBlackboardDataDetails::PostEditBlackboardProperty()
{
	UBlackboardData* BlackboardData = BlackboardDataCached.Get();
	if (BlackboardData != nullptr)
	{
		BlackboardData->Modify();
	}
	
	KeysPropertyHandleCached->NotifyPostChange(EPropertyChangeType::ValueSet);

	TSharedPtr<SBehaviorTreeBlackboardView> BlackboardView = BlackboardViewCached.Pin();
	if (BlackboardView.IsValid())
	{
		BlackboardView->RefreshGraphActionMenuItems();
	}
}

#undef LOCTEXT_NAMESPACE
