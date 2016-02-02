using UnrealBuildTool;

public class SanwuUEUtilitesSupport : ModuleRules
{
    public SanwuUEUtilitesSupport(TargetInfo TargetInfo)
    {
        PrivateDependencyModuleNames.AddRange(new string[] {
            "Core","CoreUObject","Engine","BlueprintGraph","SanwuUEUtilites"
        });
    }
}