// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SanwuUEUtilitesPrivatePCH.h"

#include "SlateBasics.h"
#include "SlateExtras.h"

#include "SanwuUEUtilitesStyle.h"
#include "SanwuUEUtilitesCommands.h"

#include "LevelEditor.h"

static const FName SanwuUEUtilitesTabName("SanwuUEUtilites");

#define LOCTEXT_NAMESPACE "FSanwuUEUtilitesModule"

void FSanwuUEUtilitesModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FSanwuUEUtilitesStyle::Initialize();
	FSanwuUEUtilitesStyle::ReloadTextures();

	FSanwuUEUtilitesCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FSanwuUEUtilitesCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FSanwuUEUtilitesModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FSanwuUEUtilitesModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FSanwuUEUtilitesModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
}

void FSanwuUEUtilitesModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FSanwuUEUtilitesStyle::Shutdown();

	FSanwuUEUtilitesCommands::Unregister();
}

void FSanwuUEUtilitesModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FSanwuUEUtilitesModule::PluginButtonClicked()")),
							FText::FromString(TEXT("SanwuUEUtilites.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FSanwuUEUtilitesModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FSanwuUEUtilitesCommands::Get().PluginAction);
}

void FSanwuUEUtilitesModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FSanwuUEUtilitesCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSanwuUEUtilitesModule, SanwuUEUtilites)