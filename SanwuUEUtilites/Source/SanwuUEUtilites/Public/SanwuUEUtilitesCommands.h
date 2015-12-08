// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
#include "SanwuUEUtilitesStyle.h"

class FSanwuUEUtilitesCommands : public TCommands<FSanwuUEUtilitesCommands>
{
public:

	FSanwuUEUtilitesCommands()
		: TCommands<FSanwuUEUtilitesCommands>(TEXT("SanwuUEUtilites"), NSLOCTEXT("Contexts", "SanwuUEUtilites", "SanwuUEUtilites Plugin"), NAME_None, FSanwuUEUtilitesStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
