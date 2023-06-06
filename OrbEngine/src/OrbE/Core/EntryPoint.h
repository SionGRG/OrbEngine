#pragma once

#include "OrbE/Core/Base.h"
#include "OrbE/Core/App.h"

#ifdef ORBE_PLATFORM_WINDOWS

extern ORB::App* ORB::CreateApplication(AppCommandLineArgs args);

int main(int argc, char** argv)
{
	ORB::Log::Init();
	
	ORBE_PROFILE_BEGIN_SESSION_DIR("Startup", "ORBProfile-Startup.json", "bin/Profiling/");
	auto app = ORB::CreateApplication({ argc, argv });
	ORBE_PROFILE_END_SESSION();

	ORBE_PROFILE_BEGIN_SESSION_DIR("Runtime", "ORBProfile-Runtime.json", "bin/Profiling/");
	app->Run();
	ORBE_PROFILE_END_SESSION();

	ORBE_PROFILE_BEGIN_SESSION_DIR("Termination", "ORBProfile-Termination.json", "bin/Profiling/");
	delete app;
	ORBE_PROFILE_END_SESSION();
}

#endif // ORBE_PLATFORM_WINDOWS
