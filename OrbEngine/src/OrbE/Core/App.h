#pragma once

#include "OrbE/Core/Base.h"

#include "OrbE/Core/Window.h"
#include "OrbE/Core/LayerStack.h"
#include "OrbE/Events/Event.h"
#include "OrbE/Events/AppEvent.h"

#include "OrbE/Core/Timestep.h"

#include "OrbE/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace ORB {

	struct AppCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			ORBE_CORE_ASSERT(index < Count);
			return Args[index];
		}
	};

	struct AppSpecification
	{
		std::string Name = "Orb App";
		std::string WorkingDirectory;
		AppCommandLineArgs CommandLineArgs;
	};

	class App
	{
	public:
		App(const AppSpecification& specification);
		virtual ~App();
				
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		Window& GetWindow() { return *m_Window; }
		static App& Get() { return *s_Instance; }

		const AppSpecification& GetSpecification() const { return m_Specification; }

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		AppSpecification m_Specification;
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static App* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// To be defined in CLIENT
	App* CreateApplication(AppCommandLineArgs args);

}
