// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SanwuBPGraphShotPrivatePCH.h"
#include "SanwuBPGraphShotCommands.h"

#define LOCTEXT_NAMESPACE "FSanwuBPGraphShotModule"

void FSanwuBPGraphShotCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "GraphShot", "Take a shot of current graph", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
