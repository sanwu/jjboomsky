// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SanwuUEUtilitesPrivatePCH.h"
#include "SanwuUEUtilitesCommands.h"

#define LOCTEXT_NAMESPACE "FSanwuUEUtilitesModule"

void FSanwuUEUtilitesCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "SanwuUEUtilites", "Execute SanwuUEUtilites action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
