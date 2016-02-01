// Copyright 1998-2016 Sanwu Games, Inc. All Rights Reserved.
#pragma once
#include "SlateBasics.h"

class SANWUUMGEXTENDER_API FSanwuUMGExtenderStyle
{
public:
	static void Initialize();
	static void Shutdown();
	static void ReloadTextures();
	static const ISlateStyle& Get();
	static FName GetStyleSetName();
private:
	static TSharedRef< class FSlateStyleSet > Create();
	static TSharedPtr< class FSlateStyleSet > UMGStyleInstance;
};
