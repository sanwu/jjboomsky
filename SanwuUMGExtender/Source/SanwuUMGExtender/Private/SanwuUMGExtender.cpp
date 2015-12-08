// Copyright 1998-2015 Sanwu Games, Inc. All Rights Reserved.

#include "SanwuUMGExtenderPrivatePCH.h"

#define LOCTEXT_NAMESPACE "FSanwuUMGExtenderModule"

void FSanwuUMGExtenderModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FSanwuUMGExtenderModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSanwuUMGExtenderModule, SanwuUMGExtender)