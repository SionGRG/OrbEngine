include "./vendor/premake/premake_customization/solution_items.lua"

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

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/OrbEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/OrbEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/OrbEngine/vendor/ImGui"
IncludeDir["ImGuizmo"] = "%{wks.location}/OrbEngine/vendor/ImGuizmo"
IncludeDir["glm"] = "%{wks.location}/OrbEngine/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/OrbEngine/vendor/stb_image"
IncludeDir["EnTT"] = "%{wks.location}/OrbEngine/vendor/EnTT/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/OrbEngine/vendor/yaml-cpp/include"

group "Dependencies"
	include "vendor/premake"
	include "OrbEngine/vendor/GLFW"
	include "OrbEngine/vendor/Glad"
	include "OrbEngine/vendor/ImGui"
	include "OrbEngine/vendor/yaml-cpp"
group ""

include "OrbEngine"
include "SandOrb"
include "Orbit"
