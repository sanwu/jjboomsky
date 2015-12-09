// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SanwuUtilitesSupport : ModuleRules
{
	public SanwuUtilitesSupport(TargetInfo Target)
	{
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "Core",
				"CoreUObject",
				"Engine",
                "SanwuUEUtilites",
                "BlueprintGraph",
            });
	}
}
