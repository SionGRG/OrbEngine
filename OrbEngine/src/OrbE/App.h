#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "OrbE/Events/AppEvent.h"
#include "Window.h"

namespace ORB {

	class ORBE_API App
	{
	public:
		App();
		virtual ~App();

		void Run();
		
		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	App* CreateApplication();


}