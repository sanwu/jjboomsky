// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
#include "SanwuBPGraphShotStyle.h"

class FSanwuBPGraphShotCommands : public TCommands<FSanwuBPGraphShotCommands>
{
public:

	FSanwuBPGraphShotCommands()
		: TCommands<FSanwuBPGraphShotCommands>(TEXT("SanwuBPGraphShot"), NSLOCTEXT("Contexts", "SanwuBPGraphShot", "SanwuBPGraphShot Plugin"), NAME_None, FSanwuBPGraphShotStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
