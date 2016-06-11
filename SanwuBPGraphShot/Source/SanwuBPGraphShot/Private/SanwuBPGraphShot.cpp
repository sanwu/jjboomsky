// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SanwuBPGraphShotPrivatePCH.h"

#include "SlateBasics.h"
#include "SlateExtras.h"

#include "SanwuBPGraphShotStyle.h"
#include "SanwuBPGraphShotCommands.h"

#include "IMainFrameModule.h"
#include "BlueprintEditorModule.h"

#include "LevelEditor.h"

static const FName SanwuBPGraphShotTabName("SanwuBPGraphShot");

#define LOCTEXT_NAMESPACE "FSanwuBPGraphShotModule"

void FSanwuBPGraphShotModule::StartupModule()
{
	FSanwuBPGraphShotStyle::Initialize();
	FSanwuBPGraphShotStyle::ReloadTextures();

	FSanwuBPGraphShotCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FSanwuBPGraphShotCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FSanwuBPGraphShotModule::PluginButtonClicked),
		FCanExecuteAction());
		
	//
	IMainFrameModule& MainFrameModule = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));
	MainFrameModule.OnMainFrameCreationFinished().AddRaw(this, &FSanwuBPGraphShotModule::OnMainFrameLoad);

}
void FSanwuBPGraphShotModule::OnMainFrameLoad(TSharedPtr<SWindow> InRootWindow, bool bIsNewProjectWindow)
{
	FBlueprintEditorModule& BlueprintEditorModule = FModuleManager::LoadModuleChecked<FBlueprintEditorModule>("Kismet");
	{
		TSharedPtr<FExtender> BPMenuExtender = MakeShareable(new FExtender());
		BPMenuExtender->AddToolBarExtension("Asset", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FSanwuBPGraphShotModule::AddToolbarExtension));
		BlueprintEditorModule.GetMenuExtensibilityManager()->AddExtender(BPMenuExtender);
	}
}
void FSanwuBPGraphShotModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FSanwuBPGraphShotStyle::Shutdown();

	FSanwuBPGraphShotCommands::Unregister();
}

void FSanwuBPGraphShotModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FSanwuBPGraphShotModule::PluginButtonClicked()")),
							FText::FromString(TEXT("SanwuBPGraphShot.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}


void FSanwuBPGraphShotModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FSanwuBPGraphShotCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSanwuBPGraphShotModule, SanwuBPGraphShot)