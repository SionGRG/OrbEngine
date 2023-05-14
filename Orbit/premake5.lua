project "Orbit"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/OrbEngine/vendor/spdlog/include",
		"%{wks.location}/OrbEngine/src",
		"%{wks.location}/OrbEngine/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.EnTT}"
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
