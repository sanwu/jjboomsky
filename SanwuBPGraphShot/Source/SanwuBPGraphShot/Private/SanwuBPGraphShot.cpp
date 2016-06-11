// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SanwuBPGraphShotPrivatePCH.h"

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "Runtime/Slate/Private/Framework/Docking/DockingPrivate.h"

#include "TabManager.h"
#include "SanwuBPGraphShotStyle.h"
#include "SanwuBPGraphShotCommands.h"

#include "IMainFrameModule.h"
#include "BlueprintEditorModule.h"

#include "LevelEditor.h"

static const FName SanwuBPGraphShotTabName("SanwuBPGraphShot");

#define LOCTEXT_NAMESPACE "FSanwuBPGraphShotModule"
DEFINE_LOG_CATEGORY_STATIC(LogBPShot, Warning, All);

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
	FSanwuBPGraphShotStyle::Shutdown();
	FSanwuBPGraphShotCommands::Unregister();
}

void FSanwuBPGraphShotModule::PluginButtonClicked()
{
	TSharedPtr<SDockTab>Tab=FGlobalTabmanager::Get()->GetActiveTab();
	TSharedPtr<class SDockingArea>TabDockingArea= Tab->GetDockArea();
	TArray<TSharedRef<SDockTab>>AllTab= TabDockingArea->GetAllChildTabs();

	for (TSharedRef<SDockTab>TabIt : AllTab)
	{
		TSharedRef<SWidget>TabContent = TabIt->GetContent();
		//UE_LOG(LogBPShot, Warning, TEXT("%s  -> %s %d  %d  %d"), *(TabIt->GetTabLabel().ToString()), *(TabContent->ToString()),TabIt->IsForeground(),TabIt->IsVolatile(),TabIt->IsVolatileIndirectly());
		//SGraphEditor
		
		if (TabIt->IsForeground()&& TabContent->ToString().Contains("SGraphEditor"))
		{
			UE_LOG(LogBPShot, Warning, TEXT("%s  -> %s "), *(TabIt->GetTabLabel().ToString()), *(TabContent->ToString()));
		}
		
	}


	FText TabName = Tab->GetTabLabel();
	TSharedPtr<SWindow>TabParentWin = Tab->GetParentWindow();
	TSharedPtr<SDockingTabWell> TabParentWell = Tab->GetParent();
	
	
}


void FSanwuBPGraphShotModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FSanwuBPGraphShotCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSanwuBPGraphShotModule, SanwuBPGraphShot)