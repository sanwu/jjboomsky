// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SanwuBPGraphShot : ModuleRules
{
	public SanwuBPGraphShot(TargetInfo Target)
	{
		
		PublicIncludePaths.AddRange(
			new string[] {
				"SanwuBPGraphShot/Public"
			});
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"SanwuBPGraphShot/Private",
			});
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "Kismet",
                "MainFrame"
			});
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Projects",
				"InputCore",
				"UnrealEd",
				"LevelEditor",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			});
	}
}
