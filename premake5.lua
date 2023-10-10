include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "OrbEngine"
	architecture "x86_64"
	startproject "Orbit"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "vendor/premake"
	include "OrbEngine/vendor/Box2D"
	include "OrbEngine/vendor/GLFW"
	include "OrbEngine/vendor/Glad"
	include "OrbEngine/vendor/ImGui"
	include "OrbEngine/vendor/yaml-cpp"
group ""

OrbRootDir = "../"

group "Core"
	include "OrbEngine"
	include "OrbScriptCore"
group ""

group "Tools"
	include "Orbit"
group ""

group "Misc"
	include "SandOrb"
group ""
