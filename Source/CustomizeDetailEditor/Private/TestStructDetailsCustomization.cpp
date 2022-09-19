#include "TestStructDetailsCustomization.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "STestStructDetailWidget.h"
#include "TestStruct.h"


#define LOCTEXT_NAMESPACE "TestStructDetailsCustomization"

TSharedRef<IPropertyTypeCustomization> FTestStructDetailsCustomization::MakeInstance()
{
	return MakeShareable(new FTestStructDetailsCustomization);
}

void FTestStructDetailsCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	static const FName HideInDetailPanelName("HideInDetailPanel");
	uint32 NumChildren;
	PropertyHandle->GetNumChildren( NumChildren );
	
	for( uint32 ChildIndex = 0; ChildIndex < NumChildren; ++ChildIndex )
	{
		TSharedRef<IPropertyHandle> ChildHandle = PropertyHandle->GetChildHandle(ChildIndex).ToSharedRef();
		if (ChildHandle->HasMetaData(HideInDetailPanelName) == false)
		{
			ChildPropertyHandles.Add( ChildHandle );
		}
	}
}

void FTestStructDetailsCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	static const FName TestValue(TEXT("TestValue"));

	StructHandle = PropertyHandle;

	for( int32 ChildIndex = 0; ChildIndex < ChildPropertyHandles.Num(); ++ChildIndex )
	{
		const TSharedRef<IPropertyHandle> ChildHandle = ChildPropertyHandles[ ChildIndex ];
		IDetailPropertyRow& PropertyRow = ChildBuilder.AddProperty( ChildHandle );
		if (ChildHandle->GetProperty()->GetFName() == TestValue)
		{
			CreateTestValueWidget(ChildHandle, PropertyRow);
		}
	}
	ChildBuilder.AddCustomRow(FText::FromString(TEXT("11")))
	.ValueContent()
	.MinDesiredWidth(500.f)
	[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot()
		.FillWidth(1.0f)
		.HAlign(HAlign_Center)
		[
			SNew(SButton)
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("11")))
			]
		]
		+SHorizontalBox::Slot()
		.FillWidth(1.0f)
		.HAlign(HAlign_Center)
		[
			SNew(SButton)
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("22222222")))
			]
		]
		+SHorizontalBox::Slot()
		.FillWidth(1.0f)
		.HAlign(HAlign_Center)
		[
			SNew(SButton)
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("333")))
			]
		]
		+SHorizontalBox::Slot()
		.FillWidth(1.0f)
		.HAlign(HAlign_Center)
		[
			SNew(SButton)
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("4444")))
			]
		]
	];
}

void FTestStructDetailsCustomization::CreateTestValueWidget(TSharedRef<IPropertyHandle> PropertyHandle, IDetailPropertyRow& PropertyRow) const
{
	PropertyRow
	.CustomWidget()
	.NameContent()
	[
		PropertyHandle->CreatePropertyNameWidget()
	]
	.ValueContent()
	.MinDesiredWidth(500.f)
	[
		SNew(STestStructDetailWidget)
		.TestValueHandle(PropertyHandle)
		.OnLoadTestStruct(FOnLoadTestStruct::CreateSP(this, &FTestStructDetailsCustomization::OnLoadTestStruct))
		.OnSaveTestStruct(FOnSaveTestStruct::CreateSP(this, &FTestStructDetailsCustomization::OnSaveTestStruct))
	];
}

void FTestStructDetailsCustomization::OnLoadTestStruct(FTestStruct TestStruct) const
{
	void* ptr = nullptr;
	StructHandle->GetValueData(ptr);
	FTestStruct* V = static_cast<FTestStruct*>(ptr);
	*V = TestStruct;
}

void FTestStructDetailsCustomization::OnSaveTestStruct(TSharedPtr<FArchive> Ar) const
{
	void* ptr = nullptr;
	StructHandle->GetValueData(ptr);
	FTestStruct* V = static_cast<FTestStruct*>(ptr);
	*Ar << *V;
}

#undef LOCTEXT_NAMESPACE
