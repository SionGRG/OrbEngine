#pragma once

#include "Core.h"
#include "Window.h"
#include "OrbE/LayerStack.h"
#include "Events/Event.h"
#include "OrbE/Events/AppEvent.h"

#include "OrbE/Core/Timestep.h"

#include "OrbE/ImGui/ImGuiLayer.h"


namespace ORB {

	class ORBE_API App
	{
	public:
		App();
		virtual ~App() = default;

		void Run();
		
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		inline static App& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static App* s_Instance;
	};

	// To be defined in CLIENT
	App* CreateApplication();


}