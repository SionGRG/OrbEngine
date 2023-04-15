#pragma once

#include "OrbE/Core/Core.h"

#include "OrbE/Core/Window.h"
#include "OrbE/Core/LayerStack.h"
#include "OrbE/Events/Event.h"
#include "OrbE/Events/AppEvent.h"

#include "OrbE/Core/Timestep.h"

#include "OrbE/ImGui/ImGuiLayer.h"


namespace ORB {

	class App
	{
	public:
		App();
		virtual ~App();

		void Run();
		
		void OnEvent(Event& e);

		void PushLayer(Ref<Layer> layer);
		void PushOverlay(Ref<Layer> overlay);

		inline Window& GetWindow() { return *m_Window; }
		inline static App& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		Scope<Window> m_Window;
		Ref<ImGuiLayer> m_ImGuiLayer;
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