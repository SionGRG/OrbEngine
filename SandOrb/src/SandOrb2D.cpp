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
	{
		ORBE_PROFILE_SCOPE("Renderer Prep");
		ORB::RenderCommand::SetClearColor({ 0.15f, 0.15f, 0.15f, 1.0f });
		ORB::RenderCommand::Clear();
	}

	{
		ORBE_PROFILE_SCOPE("Renderer Draw");
		ORB::Renderer2D::BeginScene(m_CameraController.GetCamera());
		ORB::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		ORB::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, {0.4f, 0.8f, 0.8f, 1.0f});
		ORB::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, glm::radians(80.0f) , m_CheckerboardTexture, 10.0f, ORB::v4(1.0f, 0.9f, 0.9f, 1.0f));
		ORB::Renderer2D::EndScene();
	}
}

void SandOrb2D::OnImGuiRender()
{
	ORBE_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void SandOrb2D::OnEvent(ORB::Event& e)
{
	m_CameraController.OnEvent(e);
}
