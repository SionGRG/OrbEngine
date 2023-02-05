#include "OrbPCH.h"
#include "App.h"

#include "OrbE/Events/AppEvent.h"

#include <GLFW/glfw3.h>

namespace ORB {

	App::App()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	App::~App()
	{
	}

	void App::Run()
	{
		while (m_Running)
		{
			glClearColor(0.2, 0.2, 0.2, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

}