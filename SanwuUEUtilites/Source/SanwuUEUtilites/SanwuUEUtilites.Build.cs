// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SanwuUEUtilites : ModuleRules
{
	public SanwuUEUtilites(TargetInfo Target)
	{
		
		PublicIncludePaths.AddRange(
			new string[] {
				"SanwuUEUtilites/Public"
			});
		PrivateIncludePaths.AddRange(
			new string[] {
				"SanwuUEUtilites/Private",
			});
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
                "Core","CoreUObject","Engine","InputCore"
            });
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "Core",
				"Projects",
				"InputCore",
				"UnrealEd",
				"LevelEditor",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "HTTP",
                "Networking"
			});
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
