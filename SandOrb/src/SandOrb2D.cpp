#include "SandOrb2D.h"
#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

SandOrb2D::SandOrb2D()
	: Layer("SandOrb2D"), m_CameraController(1280.0f / 720.0f)
{
}

void SandOrb2D::OnAttach()
{	
}

void SandOrb2D::OnDetach()
{
}

void SandOrb2D::OnUpdate(ORB::Timestep ts)
{
	// Update --------------------------------------------------------------
	m_CameraController.OnUpdate(ts);

	// Render --------------------------------------------------------------
	ORB::RenderCommand::SetClearColor({ 0.15f, 0.15f, 0.15f, 1.0f });
	ORB::RenderCommand::Clear();

	ORB::Renderer2D::BeginScene(m_CameraController.GetCamera());
	ORB::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	ORB::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.4f, 0.8f, 0.8f, 1.0f });
	ORB::Renderer2D::EndScene();
}

void SandOrb2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void SandOrb2D::OnEvent(ORB::Event& e)
{
	m_CameraController.OnEvent(e);
}
