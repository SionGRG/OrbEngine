#include "OrbPCH.h"
#include "OrbE/Core/App.h"

#include "OrbE/Renderer/Renderer.h"
#include "OrbE/Scripting/ScriptEngine.h"

#include "OrbE/Core/Input.h"
#include "OrbE/Utils/PlatformUtils.h"

namespace ORB {

	App* App::s_Instance = nullptr;

	App::App(const AppSpecification& specification)
		: m_Specification(specification)
	{
		ORBE_PROFILE_FUNCTION();

		ORBE_CORE_ASSERT(!s_Instance, "Application already exists!")
		s_Instance = this;

		// Set working directory
		if (!m_Specification.WorkingDirectory.empty())
			std::filesystem::current_path(m_Specification.WorkingDirectory);

		m_Window = Window::Create(WindowProps(m_Specification.Name));
		m_Window->SetEventCallback(ORBE_BIND_EVENT_FN(App::OnEvent));

		Renderer::Init();
		ScriptEngine::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	App::~App()
	{
		ORBE_PROFILE_FUNCTION();
		
		ScriptEngine::Terminate();
		Renderer::Terminate();
	}

	void App::PushLayer(Layer* layer)
	{
		ORBE_PROFILE_FUNCTION();
		
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void App::PushOverlay(Layer* overlay)
	{
		ORBE_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void App::OnEvent(Event& e)
	{
		ORBE_PROFILE_FUNCTION();
		
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(ORBE_BIND_EVENT_FN(App::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(ORBE_BIND_EVENT_FN(App::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled)
				break;

			(*it)->OnEvent(e);
		}
	}

	void App::Close()
	{
		m_Running = false;
	}

	void App::Run()
	{
		ORBE_PROFILE_FUNCTION();
		
		while (m_Running)
		{
			ORBE_PROFILE_SCOPE("Run Loop");
			
			float time = Time::GetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				{
					ORBE_PROFILE_SCOPE("LayerStack OnUpdate");
					for (auto layer : m_LayerStack)
						layer->OnUpdate(timestep);
				}
			
				m_ImGuiLayer->Begin();
				{
					ORBE_PROFILE_SCOPE("LayerStack OnImGuiRender");
					for (auto layer : m_LayerStack)
						layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}

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
		ORBE_PROFILE_FUNCTION();
		
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
