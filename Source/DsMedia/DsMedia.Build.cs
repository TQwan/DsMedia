// Copyright 2015 Headcrash Industries LLC. All Rights Reserved.

using System.IO;

namespace UnrealBuildTool.Rules
{
    using System.IO;

	public class DsMedia : ModuleRules
	{
		public DsMedia(TargetInfo Target)
		{         
            DynamicallyLoadedModuleNames.AddRange(
				new string[] {
					"Media",
                    "Settings",
				}
			);

			PrivateDependencyModuleNames.AddRange(
				new string[] {
					"Core",
                    "CoreUObject",
                    "Projects",
                    "RenderCore",
				}
			);

			PrivateIncludePathModuleNames.AddRange(
				new string[] {
					"Media",
                    "Settings",
				}
			);

			PrivateIncludePaths.AddRange(
				new string[] {
					"DsMedia/Private",
                    "DsMedia/Private/Player",
                    "DsMedia/Private/Shared",
                    "DsMedia/Private/Tracks",
                    "DsMedia/Private/Vlc",
				}
			);
		}
	}
}
