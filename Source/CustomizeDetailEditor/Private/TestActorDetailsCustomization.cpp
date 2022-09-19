#include "TestActorDetailsCustomization.h"

#include "CustomizeDetailEditorModule.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "TestActor.h"
#include "Widgets/Docking/SDockTab.h"

#define LOCTEXT_NAMESPACE "TestActorDetailsCustomization"

TSharedRef<IDetailCustomization> FTestActorDetailsCustomization::MakeInstance()
{
	return MakeShareable(new FTestActorDetailsCustomization);
}

void FTestActorDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("TestStruct");

	TSharedPtr<IPropertyHandle> TestStructProperty = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(ATestActor, TestStruct));

	FTestStruct a;
	a.TestValue = 10000;
	a.TestFloat = 20000.f;
	a.TestMap.Emplace(50, 50);
	a.TestMap.Emplace(500, 500);
	a.TestMap.Emplace(5000, 5000);
	

	void* ptr = nullptr;
	TestStructProperty->GetValueData(ptr);
	
	FTestStruct* b = static_cast<FTestStruct*>(ptr);

	*b = a;

	Category.AddCustomRow(FText::FromString(TEXT("11")))
	.NameContent()
	[
		SNew(STextBlock)
		.Text(FText::FromString(TEXT("DDDDD")))
	]
	.WholeRowContent()
	[
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		[
			SNew(SButton)
		]
	]
	.ValueContent()
	[
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		[
			SNew(SButton)
			.OnClicked(FOnClicked::CreateSP(this, &FTestActorDetailsCustomization::OnClicked))
		]
		+SVerticalBox::Slot()
		[
			SNew(SButton)
		]
		+SVerticalBox::Slot()
		[
			SNew(SButton)
		]
		+SVerticalBox::Slot()
		[
			SNew(SButton)
		]
		+SVerticalBox::Slot()
		[
			SNew(SButton)
		]
	];
	

	// Category.AddCustomBuilder()
}

FReply FTestActorDetailsCustomization::OnClicked() const
{
	ICustomizeDetailEditorModule& CustomizeDetailEditorModule = FModuleManager::GetModuleChecked<ICustomizeDetailEditorModule>("CustomizeDetailEditor");
	return CustomizeDetailEditorModule.OnClicked();
}

#undef LOCTEXT_NAMESPACE