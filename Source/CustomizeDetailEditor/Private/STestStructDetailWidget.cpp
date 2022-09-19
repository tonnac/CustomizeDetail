// Fill out your copyright notice in the Description page of Project Settings.


#include "STestStructDetailWidget.h"

#include "CustomizeDetailEditorHelperMethods.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "SlateOptMacros.h"
#include "TestStruct.h"
#include "TestTable.h"
#include "Widgets/Input/SNumericEntryBox.h"

#define LOCTEXT_NAMESPACE "TestStructDetail"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void STestStructDetailWidget::Construct(const FArguments& InArgs)
{
	TestValueHandle = InArgs._TestValueHandle;
	OnLoadTestStruct = InArgs._OnLoadTestStruct;
	OnSaveTestStruct = InArgs._OnSaveTestStruct;

	ChildSlot
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		.FillWidth(1.0f)
		.HAlign(HAlign_Fill)
		[
			SNew(SNumericEntryBox<int32>)
			.Value(this, &STestStructDetailWidget::GetTestValue)
			.IsEnabled(false)
		]
		+SHorizontalBox::Slot()
		.FillWidth(4.0f)
		.HAlign(HAlign_Fill)
		[
			SNew(SComboButton)
			.OnGetMenuContent(this, &STestStructDetailWidget::OnGetComboContent)
			.ButtonContent()
			[
				SAssignNew(ValueText, STextBlock)
			]
		]
		+SHorizontalBox::Slot()
		.FillWidth(1.0f)
		.HAlign(HAlign_Fill)
		[
			SNew(SButton)
			.Text(FText::FromString(TEXT("Open")))
			.OnClicked(FOnClicked::CreateSP(this, &STestStructDetailWidget::OnClicked_Button))
		]
		+SHorizontalBox::Slot()
		.FillWidth(1.0f)
		.HAlign(HAlign_Fill)
		[
			SNew(SButton)
			.Text(FText::FromString(TEXT("Save")))
			.OnClicked(FOnClicked::CreateSP(this, &STestStructDetailWidget::OnClicked_SaveButton))
		]
	];
}

TOptional<int32> STestStructDetailWidget::GetTestValue() const
{
	int32 Value = 0;
	if (TestValueHandle->GetValue(Value) == FPropertyAccess::Success)
	{
		TextSet(Value);
		return Value;
	}
	return TOptional<int32>();
}

TSharedRef<SWidget> STestStructDetailWidget::OnGetComboContent() const
{
	// Fill the combo menu with presets of common screen resolutions
	FMenuBuilder MenuBuilder(true, NULL);

	for (auto TableIter = FCustomizeDetailEditorHelperMethods::GetTables().CreateConstIterator(); TableIter; ++TableIter)
	{
		FTestTable* Table = TableIter->Value;
		FUIAction ItemAction( FExecuteAction::CreateSP( const_cast<STestStructDetailWidget*>(this), &STestStructDetailWidget::CommitAspectRatioText, Table ) );
		MenuBuilder.AddMenuEntry(Table->AAA, TAttribute<FText>(), FSlateIcon(), ItemAction);
	}

	return MenuBuilder.MakeWidget();
}

void STestStructDetailWidget::CommitAspectRatioText(FTestTable* Table)
{
	TestValueHandle->SetValue(Table->NNN);
	TextSet(Table);
}

FReply STestStructDetailWidget::OnClicked_Button()
{
	TArray<FString> OpenedFiles;
	
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	DesktopPlatform->OpenFileDialog(
		FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr),
		LOCTEXT("Open!!!", "Open@@@").ToString(),
		FString(),
		TEXT(""),
		TEXT("Text Files|*.txt|"),
		EFileDialogFlags::None,
		OpenedFiles
		);
	if (OpenedFiles.Num() > 0)
	{
		TSharedPtr<FArchive> Ar = MakeShareable(IFileManager::Get().CreateFileReader(*OpenedFiles[0]));

		if (Ar.IsValid())
		{
			FTestStruct a;
			*Ar << a;

			if (OnLoadTestStruct.IsBound())
			{
				OnLoadTestStruct.Execute(a);
			}
		}
	}
	

	return FReply::Handled();
}

FReply STestStructDetailWidget::OnClicked_SaveButton()
{
	TArray<FString> OpenedFiles;
	
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	DesktopPlatform->SaveFileDialog(
		FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr),
		LOCTEXT("Save!!!", "Save@@@").ToString(),
		FString(),
		TEXT(""),
		TEXT("Text Files|*.txt|"),
		EFileDialogFlags::None,
		OpenedFiles
		);
	if (OpenedFiles.Num() > 0)
	{
		TSharedPtr<FArchive> Ar = MakeShareable(IFileManager::Get().CreateFileWriter(*OpenedFiles[0]));
		if (OnSaveTestStruct.IsBound())
		{
			OnSaveTestStruct.Execute(Ar);
		}
	}
	

	return FReply::Handled();
}

void STestStructDetailWidget::TextSet(const FTestTable* TestTable) const
{
	if (TestTable)
	{
		ValueText->SetText(TestTable->AAA);
	}
	else
	{
		ValueText->SetText(FText::GetEmpty());
	}
}

void STestStructDetailWidget::TextSet(int32 Key) const
{
	TextSet(FCustomizeDetailEditorHelperMethods::GetTable(Key));
}

#undef LOCTEXT_NAMESPACE

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
