#include "SandOrb2D.h"

#include <ImGui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

template<typename Fn>
class Timer {
public:
	Timer(const char* name, Fn&& func)
		: m_Name(name), m_Stopped(false), m_Func(func)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;

		float duration = (end - start) * 0.001f;
		m_Func({ m_Name, duration });
	}

private:
	const char* m_Name;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
	Fn m_Func;
};

// Timer Definition --------------------------------------------------------------
#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })

SandOrb2D::SandOrb2D()
	: Layer("SandOrb2D"), m_CameraController(1280.0f / 720.0f)
{
}

void SandOrb2D::OnAttach()
{
	m_CheckerboardTexture = ORB::Texture2D::Create("assets/textures/Checkerboard.png");

}

void SandOrb2D::OnDetach()
{
}

void SandOrb2D::OnUpdate(ORB::Timestep ts)
{
	PROFILE_SCOPE("SandOrb2D::OnUpdate");

	// Update --------------------------------------------------------------
	{
		PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	// Render --------------------------------------------------------------
	{
		PROFILE_SCOPE("Renderer Prep");
		ORB::RenderCommand::SetClearColor({ 0.15f, 0.15f, 0.15f, 1.0f });
		ORB::RenderCommand::Clear();
	}

	{
		PROFILE_SCOPE("Renderer Draw");
		ORB::Renderer2D::BeginScene(m_CameraController.GetCamera());
		ORB::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		ORB::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.4f, 0.8f, 0.8f, 1.0f });
		ORB::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
		ORB::Renderer2D::EndScene();
	}
}

void SandOrb2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::Text("\n==== PERFORMANCE PROFILING ====");
	for (auto& result : m_ProfileResults)
	{
		char label[50];
		strcpy(label, "%.3fms ");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();

	ImGui::End();
}

void SandOrb2D::OnEvent(ORB::Event& e)
{
	m_CameraController.OnEvent(e);
}
