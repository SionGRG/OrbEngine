#include "SandOrb2D.h"

#include <ImGui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

SandOrb2D::SandOrb2D()
	: Layer("SandOrb2D"), m_CameraController(1280.0f / 720.0f), m_SquareColor({ 0.4f, 0.8f, 0.8f, 1.0f })
{
}

void SandOrb2D::OnAttach()
{
	ORBE_PROFILE_FUNCTION();

	m_CheckerboardTexture = ORB::Texture2D::Create("assets/textures/Checkerboard.png");
	m_SpaceShooterTexture = ORB::Texture2D::Create("Game/Textures/spaceshooter.png");
	
	m_SpaceShipsSubTexture = ORB::SubTexture2D::CreateFromCoords(m_SpaceShooterTexture, { 817.0f, -6.0f - 768.0f }, { 614.0f, 768.0f });
	//m_ExplosionSubTexture = ORB::SubTexture2D::CreateFromCoords(m_SpaceShooterTexture, { 530.0f, -819.0f - 416.0f }, { 490.0f, 416.0f });
	//m_ExplosionSubTexture = ORB::SubTexture2D::CreateFromRECT(m_SpaceShooterTexture, { 530.0f, -819.0f - 416.0f, 490.0f, 416.0f });
	m_ExplosionSubTexture = ORB::SubTexture2D::CreateFromRECT_BL(m_SpaceShooterTexture, { 530.0f, 819.0f, 490.0f, 416.0f });

	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 5.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };

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
		ORBE_PROFILE_SCOPE("Renderer Draw");

#if 0
		static float rotation = 0.0f;
		rotation += ts * 50.0f;
		
		ORB::Renderer2D::BeginScene(m_CameraController.GetCamera());
		ORB::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-rotation) * 0.2f, { 0.8f, 0.6f, 0.1f, 1.0f });
		ORB::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		ORB::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColor);
		ORB::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
		ORB::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(rotation), m_CheckerboardTexture, 20.0f);
		ORB::Renderer2D::EndScene();
#endif // 0
		
		// Grid
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

		ORB::Renderer2D::BeginScene(m_CameraController.GetCamera());
		ORB::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_SpaceShipsSubTexture);
		ORB::Renderer2D::DrawQuad({ 1.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_ExplosionSubTexture);
		ORB::Renderer2D::EndScene();
	}

	// Particles
	if (ORB::Input::IsMouseButtonPressed(ORBE_MOUSE_BUTTON_LEFT))
	{
		auto [x, y] = ORB::Input::GetMousePosition();
		auto width = ORB::App::Get().GetWindow().GetWidth();
		auto height = ORB::App::Get().GetWindow().GetHeight();

		auto bounds = m_CameraController.GetBounds();
		auto pos = m_CameraController.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_Particle.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 5; i++)
			m_ParticleSystem.Emit(m_Particle);
	}

	m_ParticleSystem.OnUpdate(ts);
	m_ParticleSystem.OnRender(m_CameraController.GetCamera());
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
