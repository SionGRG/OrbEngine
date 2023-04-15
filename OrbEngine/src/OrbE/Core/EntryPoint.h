#pragma once

#include "OrbE/Core/Core.h"

#ifdef ORBE_PLATFORM_WINDOWS

extern ORB::App* ORB::CreateApplication();

int main(int argc, char** argv)
{
	ORB::Log::Init();
	
	ORBE_PROFILE_BEGIN_SESSION("Startup", "ORBProfile-Startup.json");
	auto app = ORB::CreateApplication();
	ORBE_PROFILE_END_SESSION();

	ORBE_PROFILE_BEGIN_SESSION("Runtime", "ORBProfile-Runtime.json");
	app->Run();
	ORBE_PROFILE_END_SESSION();

	ORBE_PROFILE_BEGIN_SESSION("Termination", "ORBProfile-Termination.json");
	delete app;
	ORBE_PROFILE_END_SESSION();
}

#endif // ORBE_PLATFORM_WINDOWS
