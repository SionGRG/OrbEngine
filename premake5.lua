workspace "OrbEngine"
	architecture "x64"
	startproject "SandOrb"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "OrbEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "OrbEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "OrbEngine/vendor/ImGui"

group "Dependencies"
	include "OrbEngine/vendor/GLFW"
	include "OrbEngine/vendor/Glad"
	include "OrbEngine/vendor/ImGui"

group ""

project "OrbEngine"
	location "OrbEngine"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "OrbPCH.h"
	pchsource "OrbEngine/src/OrbPCH.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"

		defines
		{
			"ORBE_PLATFORM_WINDOWS",
			"ORBE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/SandOrb/\"")
		}

	filter "configurations:Debug"
		defines "ORBE_DEBUG"
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		defines "ORBE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "ORBE_DIST"
		runtime "Release"
		optimize "On"

project "SandOrb"
	location "SandOrb"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		"OrbEngine/src"
	}

	links
	{
		"OrbEngine"
	}

	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"

		defines
		{
			"ORBE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ORBE_DEBUG"
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		defines "ORBE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "ORBE_DIST"
		runtime "Release"
		optimize "On"