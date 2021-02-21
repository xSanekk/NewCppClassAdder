#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Slate/Public/Framework/MultiBox/MultiBoxBuilder.h"

class FNewCppClassAdderModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;

private:
	static void AddCppEntryToContentBrowser(FMenuBuilder& Builder);
};
