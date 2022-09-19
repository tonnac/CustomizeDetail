// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestStruct.h"
#include "Widgets/SCompoundWidget.h"

DECLARE_DELEGATE_OneParam(FOnLoadTestStruct, FTestStruct)
DECLARE_DELEGATE_OneParam(FOnSaveTestStruct, TSharedPtr<FArchive>)

struct FTestTable;
/**
 * 
 */
class CUSTOMIZEDETAILEDITOR_API STestStructDetailWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STestStructDetailWidget) {}
		SLATE_ARGUMENT(TSharedPtr<IPropertyHandle>, TestValueHandle)
		SLATE_ARGUMENT(FOnLoadTestStruct, OnLoadTestStruct)
		SLATE_ARGUMENT(FOnSaveTestStruct, OnSaveTestStruct)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	TOptional<int32> GetTestValue() const;

	TSharedRef<SWidget> OnGetComboContent() const;
	void CommitAspectRatioText(FTestTable* Table);

	FReply OnClicked_Button();
	FReply OnClicked_SaveButton();

	void TextSet(const FTestTable* TestTable) const;
	void TextSet(int32 Key) const;


private:
	TSharedPtr<STextBlock> ValueText;
	TSharedPtr<IPropertyHandle> TestValueHandle;

	FOnLoadTestStruct OnLoadTestStruct;
	FOnSaveTestStruct OnSaveTestStruct;
};
