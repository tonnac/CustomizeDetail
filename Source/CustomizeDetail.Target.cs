// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CustomizeDetailTarget : TargetRules
{
	public CustomizeDetailTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "CustomizeDetail" } );

		if (bBuildEditor)
		{
			ExtraModuleNames.Add("CustomizeDetailEditor");
		}
	}
}
 