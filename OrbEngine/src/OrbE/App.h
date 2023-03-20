#pragma once

#include "Core.h"
#include "Window.h"
#include "OrbE/LayerStack.h"
#include "Events/Event.h"
#include "OrbE/Events/AppEvent.h"

namespace ORB {

	class ORBE_API App
	{
	public:
		App();
		virtual ~App();

		void Run();
		
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		inline static App& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static App* s_Instance;
	};

	// To be defined in CLIENT
	App* CreateApplication();


}