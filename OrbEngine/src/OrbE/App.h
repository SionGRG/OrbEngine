#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace ORB {

	class ORBE_API App
	{
	public:
		App();
		virtual ~App();

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	App* CreateApplication();


}