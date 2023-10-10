OrbRootDir = "../../../.."

include (OrbRootDir .. "/vendor/premake/premake_customization/solution_items.lua")

workspace "SandOrb"
	architecture "x86_64"
	startproject "SandOrb"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "SandOrb"
	kind "SharedLib"
	language "C#"
	dotnetframework "4.7.2"

	targetdir ("Binaries")
	objdir ("Intermediates")

	pchheader "OrbPCH.h"
	pchsource "src/OrbPCH.cpp"

	files
	{
		"Source/**.cs",
		"Properties/**.cs"
	}

	links
	{
		"OrbScriptCore"
	}

	filter "configurations:Debug"
		optimize "Off"
		symbols "Default"

	filter "configurations:Release"
		optimize "On"
		symbols "Default"
		
	filter "configurations:Dist"
		optimize "Full"
		symbols "Off"

group "ORB"
	include (OrbRootDir .. "/OrbScriptCore")
group ""