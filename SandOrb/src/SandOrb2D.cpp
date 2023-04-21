#include "SandOrb2D.h"

#include <ImGui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

SandOrb2D::SandOrb2D()
	: Layer("SandOrb2D"), m_CameraController(1280.0f / 720.0f)
{
}

void SandOrb2D::OnAttach()
{
	ORBE_PROFILE_FUNCTION();

	m_CheckerboardTexture = ORB::Texture2D::Create("assets/textures/Checkerboard.png");

}

void SandOrb2D::OnDetach()
{
	ORBE_PROFILE_FUNCTION();

}

void SandOrb2D::OnUpdate(ORB::Timestep ts)
{
	ORBE_PROFILE_FUNCTION();

	// Update --------------------------------------------------------------
	m_CameraController.OnUpdate(ts);
	
	// Render --------------------------------------------------------------
	ORB::Renderer2D::ResetStats();
	{
		ORBE_PROFILE_SCOPE("Renderer Prep");
		ORB::RenderCommand::SetClearColor({ 0.15f, 0.15f, 0.15f, 1.0f });
		ORB::RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f

		ORBE_PROFILE_SCOPE("Renderer Draw");
		ORB::Renderer2D::BeginScene(m_CameraController.GetCamera());
		ORB::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -rotation * 0.2f, { 0.8f, 0.6f, 0.1f, 1.0f });
		ORB::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		ORB::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, {0.4f, 0.8f, 0.8f, 1.0f});
		ORB::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
		ORB::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 20.0f);
		ORB::Renderer2D::EndScene();
		
		ORB::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				ORB::v4 color = { (x + 5.0f) / 10.0f, 0.3f, (y + 5.0f) / 10.0f, 0.7f };
				ORB::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		ORB::Renderer2D::EndScene();
	}
}

void SandOrb2D::OnImGuiRender()
{
	ORBE_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = ORB::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());


	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void SandOrb2D::OnEvent(ORB::Event& e)
{
	m_CameraController.OnEvent(e);
}
