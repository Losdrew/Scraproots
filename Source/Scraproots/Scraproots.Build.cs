// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Scraproots : ModuleRules
{
    public Scraproots(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "EnhancedInput",
                "GameplayTags",
                "CommonUI",
                "UMG",
                "DeveloperSettings"
            }
        );
    }
}
