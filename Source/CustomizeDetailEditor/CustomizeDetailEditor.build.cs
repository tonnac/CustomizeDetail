
using UnrealBuildTool;

public class CustomizeDetailEditor : ModuleRules
{
    public CustomizeDetailEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivateIncludePaths.AddRange(new string[]
        {
            ModuleDirectory + "/Private",
            ModuleDirectory + "/Public"
        });

        // PublicIncludePathModuleNames.AddRange(
        //     new string[] {
        //     }
        // );

        // PublicDependencyModuleNames.AddRange(
        //     new string[]
        //     {
        //     }
        // );

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "ApplicationCore",
                "Slate",
                "SlateCore",
                "CustomizeDetail",
                "PropertyEditor",
                "InputCore",
                "EditorStyle",
                "Engine",
                "DesktopPlatform",
                "UMG",
                "UnrealEd",
                "AdvancedPreviewScene"
            }
        );
    }
}