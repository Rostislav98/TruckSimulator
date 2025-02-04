// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Gameplay : ModuleRules
{
	public Gameplay(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "UI", "GameAI", "UMG", "NavigationSystem"
			}
			);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
			}
			);
	
	}
}
