#pragma once

#include "OrbE/Core/Core.h"

#ifdef ORBE_PLATFORM_WINDOWS

extern ORB::Scope<ORB::App> ORB::CreateApplication();

int main(int argc, char** argv)
{
	ORB::Log::Init();
	ORBE_CORE_WARN("Initialized Log!");
	int a = 5;
	ORBE_INFO("Hello! Var={0}", a);

	auto app = ORB::CreateApplication();
	app->Run();
}

#endif // ORBE_PLATFORM_WINDOWS
