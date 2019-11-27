// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ScreenStackEditor : ModuleRules
{
	public ScreenStackEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                // ... add other public dependencies that you statically link with here ...
			}
		);
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...
				"CoreUObject",
				"Slate",
				"Engine",
				"UnrealEd", // for FAssetEditorManager
				"KismetCompiler",
				"BlueprintGraph",
				"Slate",
				"SlateCore",
                "UMG",
                "ScreenStackRuntime"
            }
        );
			}
}
