#include "NewCppClassAdder.h"

#include <ContentBrowser/Public/ContentBrowserModule.h>
#include <GameProjectGeneration/Public/GameProjectGenerationModule.h>

#define LOCTEXT_NAMESPACE "FNewCppClassAdderModule"

void FNewCppClassAdderModule::StartupModule()
{
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	TArray<FContentBrowserMenuExtender_SelectedPaths>& ContextMenuExtenders = ContentBrowserModule.GetAllAssetContextMenuExtenders();
	ContextMenuExtenders.Add(FContentBrowserMenuExtender_SelectedPaths::CreateLambda(
        [&](const TArray<FString>& SelectedPaths) 
        {
            TSharedPtr<FExtender> ClassAdderExtender = MakeShared<FExtender>();

            ClassAdderExtender->AddMenuExtension(
            	"ContentBrowserImportAsset",
            	EExtensionHook::After,
            	TSharedPtr<FUICommandList>(),
            	FMenuExtensionDelegate::CreateStatic(&FNewCppClassAdderModule::AddCppEntryToContentBrowser));

        	return ClassAdderExtender.ToSharedRef();
        }));
}

void FNewCppClassAdderModule::AddCppEntryToContentBrowser(FMenuBuilder& Builder)
{
	const auto ExecuteAction(FExecuteAction::CreateLambda(
		[]
		{
			FGameProjectGenerationModule::Get().OpenAddCodeToProjectDialog();
		}));
	
	Builder.BeginSection("ContentBrowserNewClass", LOCTEXT("ClassMenuHeading", "C++ Class"));
	Builder.AddMenuEntry(
		LOCTEXT("NewClassLabel", "New C++ Class..."),
		LOCTEXT("NewClassTooltip_CreateInDefault", "Create a new C++ class in your project's source folder"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "MainFrame.AddCodeToProject"),
		FUIAction(ExecuteAction));
	Builder.EndSection();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNewCppClassAdderModule, NewCppClassAdder)
