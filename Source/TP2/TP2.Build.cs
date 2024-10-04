// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TP2 : ModuleRules
{
	public TP2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
