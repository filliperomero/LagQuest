// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LagQuest : ModuleRules
{
	public LagQuest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"NetCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"LagQuest",
			"LagQuest/Variant_Platforming",
			"LagQuest/Variant_Platforming/Animation",
			"LagQuest/Variant_Combat",
			"LagQuest/Variant_Combat/AI",
			"LagQuest/Variant_Combat/Animation",
			"LagQuest/Variant_Combat/Gameplay",
			"LagQuest/Variant_Combat/Interfaces",
			"LagQuest/Variant_Combat/UI",
			"LagQuest/Variant_SideScrolling",
			"LagQuest/Variant_SideScrolling/AI",
			"LagQuest/Variant_SideScrolling/Gameplay",
			"LagQuest/Variant_SideScrolling/Interfaces",
			"LagQuest/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
