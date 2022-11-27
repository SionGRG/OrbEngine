#include "App.h"

#include "OrbE/Events/AppEvent.h"
#include "OrbE/Log.h"

namespace ORB {

	App::App()
	{
	}

	App::~App()
	{
	}

	void App::Run()
	{
		WindowResizeEvent e(1280, 720);
		ORBE_TRACE(e);

		while (true);
	}

}