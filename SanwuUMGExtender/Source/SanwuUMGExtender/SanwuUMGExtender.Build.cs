// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SanwuUMGExtender : ModuleRules
{
	public SanwuUMGExtender(TargetInfo Target)
	{
		
		PublicIncludePaths.AddRange(
			new string[] {
				"SanwuUMGExtender/Public"
			});
		PrivateIncludePaths.AddRange(
			new string[] {
				"SanwuUMGExtender/Private",
			});
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			});
			
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "Core",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "UMG"
			});
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
