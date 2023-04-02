#pragma once

#include "Core.h"
#include "Window.h"
#include "OrbE/LayerStack.h"
#include "Events/Event.h"
#include "OrbE/Events/AppEvent.h"

#include "OrbE/ImGui/ImGuiLayer.h"

#include "OrbE/Renderer/Shader.h"
#include "OrbE/Renderer/Buffer.h"
#include "OrbE/Renderer/VertexArray.h"

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
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_SquareShader;
		std::shared_ptr<VertexArray> m_SquareVA;

	private:
		static App* s_Instance;
	};

	// To be defined in CLIENT
	App* CreateApplication();


}