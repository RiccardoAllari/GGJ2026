// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GGJ2026 : ModuleRules
{
	public GGJ2026(ReadOnlyTargetRules Target) : base(Target)
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
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"GGJ2026",
			"GGJ2026/Variant_Horror",
			"GGJ2026/Variant_Horror/UI",
			"GGJ2026/Variant_Shooter",
			"GGJ2026/Variant_Shooter/AI",
			"GGJ2026/Variant_Shooter/UI",
			"GGJ2026/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
