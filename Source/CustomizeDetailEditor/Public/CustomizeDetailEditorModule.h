#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class ICustomizeDetailEditorModule : public IModuleInterface
{
	virtual void StartupModule() override = 0;
	virtual void ShutdownModule() override = 0;
public:
	virtual FReply OnClicked() const = 0;
};
