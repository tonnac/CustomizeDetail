#pragma once
#include "IPropertyTypeCustomization.h"
#include "TestStruct.h"

struct FTestTable;
class IDetailPropertyRow;
class IPropertyHandle;

class FTestStructDetailsCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;

private:
	void CreateTestValueWidget(TSharedRef<IPropertyHandle> PropertyHandle, IDetailPropertyRow& PropertyRow) const;

	void OnLoadTestStruct(FTestStruct TestStruct) const;
	void OnSaveTestStruct(TSharedPtr<FArchive> Ar) const;
	
private:
	TSharedPtr<IPropertyHandle> StructHandle;
	TArray< TSharedRef<IPropertyHandle> > ChildPropertyHandles;
};

