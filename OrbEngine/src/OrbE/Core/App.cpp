#include "OrbPCH.h"
#include "OrbE/Core/App.h"

#include "OrbE/Renderer/Renderer.h"

#include "OrbE/Core/Input.h"

#include <GLFW/glfw3.h>

namespace ORB {

	App* App::s_Instance = nullptr;

	App::App()
	{
		ORBE_CORE_ASSERT(!s_Instance, "Application already exists!")
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(ORBE_BIND_EVENT_FN(App::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = CreateRef<ImGuiLayer>();
		PushOverlay(m_ImGuiLayer);
	}

	App::~App()
	{
		Renderer::Terminate();
	}

	void App::PushLayer(Ref<Layer> layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void App::PushOverlay(Ref<Layer> overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void App::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(ORBE_BIND_EVENT_FN(App::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(ORBE_BIND_EVENT_FN(App::OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void App::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				for (auto layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}
			
			m_ImGuiLayer->Begin();
			for (auto layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool App::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool App::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

}