// Copyright 1998-2015 Sanwu Games, Inc. All Rights Reserved.

#include "SanwuUMGExtenderPrivatePCH.h"
#include "SanwuUMGExtenderStyle.h"
#define LOCTEXT_NAMESPACE "FSanwuUMGExtenderModule"

void FSanwuUMGExtenderModule::StartupModule()
{
#if WITH_EDITOR
	if (GIsEditor)
	{
		FSanwuUMGExtenderStyle::Initialize();
	}
#endif
	
	
}

void FSanwuUMGExtenderModule::ShutdownModule()
{
#if WITH_EDITOR
	if (GIsEditor)
	{
		FSanwuUMGExtenderStyle::Shutdown();
	}
#endif
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSanwuUMGExtenderModule, SanwuUMGExtender)