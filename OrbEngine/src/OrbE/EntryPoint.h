#pragma once

#ifdef ORBE_PLATFORM_WINDOWS

extern ORB::App* ORB::CreateApplication();

int main(int argc, char** argv)
{
	auto app = ORB::CreateApplication();
	app->Run();
	delete app;
}

#endif // ORBE_PLATFORM_WINDOWS
