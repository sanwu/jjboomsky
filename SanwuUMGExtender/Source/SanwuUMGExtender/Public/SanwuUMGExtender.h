// Copyright 1998-2016 Sawnu Games, Inc. All Rights Reserved.

#pragma once

#include "ModuleManager.h"

class FSanwuUMGExtenderModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};