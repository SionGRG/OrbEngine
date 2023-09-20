project "OrbScriptCore"
	kind "SharedLib"
	language "C#"
	dotnetframework "4.7.2"

	targetdir ("%{wks.location}/Orbit/Resources/Scripts")
	objdir ("%{wks.location}/Orbit/Resources/Scripts/Intermediates")

	pchheader "OrbPCH.h"
	pchsource "src/OrbPCH.cpp"

	files
	{
		"Source/**.cs",
		"Properties/**.cs"
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
