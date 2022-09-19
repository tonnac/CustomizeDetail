#include "CustomizeDetailEditorModule.h"
#include "CustomizeDetailEditorLog.h"
#include "PropertyEditorModule.h"
#include "STestTab.h"
#include "TestActorDetailsCustomization.h"
#include "TestStructDetailsCustomization.h"
#include "Widgets/Docking/SDockTab.h"


class FCustomizeDetailEditorModule : public ICustomizeDetailEditorModule
{
	virtual void StartupModule() override
	{
		DETAIL_EDITOR_LOG(TEXT("Start"));
		// check(PropertyTypeName != NAME_None);
		//
		// RegisteredPropertyTypes.Add(PropertyTypeName);

		static FName PropertyEditor("PropertyEditor");
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(PropertyEditor);
		PropertyModule.RegisterCustomPropertyTypeLayout("TestStruct", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FTestStructDetailsCustomization::MakeInstance));
		PropertyModule.RegisterCustomClassLayout("TestActor", FOnGetDetailCustomizationInstance::CreateStatic(&FTestActorDetailsCustomization::MakeInstance));
		
		FGlobalTabmanager::Get()->RegisterTabSpawner(
			TabId,
			FOnSpawnTab::CreateStatic(&SpawnTab))
		.SetDisplayName(NSLOCTEXT("UnrealEditor", "MessageLogTab", "Message Log"))
		.SetTooltipText(NSLOCTEXT("UnrealEditor", "MessageLogTooltipText", "Open the Message Log tab."))
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "MessageLog.TabIcon"));
	}
	
	virtual void ShutdownModule() override
	{
		
	}

public:
	virtual FReply OnClicked() const override;
	
private:
	static const FName TabId;
	static TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& SpawnTabArgs);
};

const FName FCustomizeDetailEditorModule::TabId = TEXT("TestTabId");

TSharedRef<SDockTab> FCustomizeDetailEditorModule::SpawnTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::MajorTab)
	[
		SNew(STestTab)
	];
}

FReply FCustomizeDetailEditorModule::OnClicked() const
{
	FGlobalTabmanager::Get()->TryInvokeTab(TabId);
	return FReply::Handled();
}


IMPLEMENT_MODULE(FCustomizeDetailEditorModule, CustomizeDetailEditor);
