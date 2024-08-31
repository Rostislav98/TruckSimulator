// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameAI : ModuleRules
{
	public GameAI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "AIModule", "UMG"
            }
			);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"Gameplay", 
				"UI", "GameCore"
            }
			);
	
	}
}
