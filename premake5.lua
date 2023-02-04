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

project "OrbEngine"
	location "OrbEngine"
	kind "SharedLib"
	language "C++"

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
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ORBE_PLATFORM_WINDOWS",
			"ORBE_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandOrb")
		}

	filter "configurations:Debug"
		defines "ORBE_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "ORBE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ORBE_DIST"
		optimize "On"

project "SandOrb"
	location "SandOrb"
	kind "ConsoleApp"
	language "C++"

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
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ORBE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ORBE_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "ORBE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ORBE_DIST"
		optimize "On"