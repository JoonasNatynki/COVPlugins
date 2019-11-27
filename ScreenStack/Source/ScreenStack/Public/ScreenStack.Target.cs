// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class ScreenStackTarget : TargetRules
{
	public ScreenStackTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		//ExtraModuleNames.AddRange( new string[] { "COV" } );
	}
}
