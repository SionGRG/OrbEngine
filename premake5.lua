workspace "OrbEngine"
	architecture "x86_64"
	startproject "Orbit"
	
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

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "OrbEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "OrbEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "OrbEngine/vendor/ImGui"
IncludeDir["glm"] = "OrbEngine/vendor/glm"
IncludeDir["stb_image"] = "OrbEngine/vendor/stb_image"

group "Dependencies"
	include "OrbEngine/vendor/GLFW"
	include "OrbEngine/vendor/Glad"
	include "OrbEngine/vendor/ImGui"

group ""

project "OrbEngine"
	location "OrbEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "OrbPCH.h"
	pchsource "OrbEngine/src/OrbPCH.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ORBE_BUILD_DLL"
		}

	filter "configurations:Debug"
		defines "ORBE_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "ORBE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ORBE_DIST"
		runtime "Release"
		optimize "on"

project "SandOrb"
	location "SandOrb"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"OrbEngine/vendor/spdlog/include",
		"OrbEngine/src",
		"OrbEngine/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"OrbEngine"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "ORBE_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "ORBE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ORBE_DIST"
		runtime "Release"
		optimize "on"

project "Orbit"
	location "Orbit"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"OrbEngine/vendor/spdlog/include",
		"OrbEngine/src",
		"OrbEngine/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"OrbEngine"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "ORBE_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "ORBE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ORBE_DIST"
		runtime "Release"
		optimize "on"