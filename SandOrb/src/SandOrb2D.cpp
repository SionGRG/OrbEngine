#include "SandOrb2D.h"

#include <ImGui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


static const uint32_t s_MapWidth = 24;
static const char* s_MapTiles =
"AAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAFFFFFFAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAA"
"AAAAAAAAAAAAAAAAAAAAAAAA"
;

static const uint32_t s_PacmanMapWidth = 26;
static const char* s_PacmanMapTiles =
"............xx............"
".xxxx.xxxxx.xx.xxxxx.xxxx."
"ox--x.x---x.xx.x---x.x--xo"
".xxxx.xxxxx.xx.xxxxx.xxxx."
".........................."
".xxxx.xx.xxxxxxxx.xx.xxxx."
".xxxx.xx.xxxxxxxx.xx.xxxx."
"......xx....xx....xx......"
"xxxxx.xxxxx xx xxxxx.xxxxx"
"----x.xxxxx xx xxxxx.x----"
"----x.xx          xx.x----"
"----x.xx xxx  xxx xx.x----"
"xxxxx.xx x      x xx.xxxxx"
"     .   x      x   .     "
"xxxxx.xx x      x xx.xxxxx"
"----x.xx xxxxxxxx xx.x----"
"----x.xx          xx.x----"
"----x.xx xxxxxxxx xx.x----"
"xxxxx.xx xxxxxxxx xx.xxxxx"
"............xx............"
".xxxx.xxxxx.xx.xxxxx.xxxx."
".xxxx.xxxxx.xx.xxxxx.xxxx."
"...xx........p.......xx..."
"xx.xx.xx.xxxxxxxx.xx.xx.xx"
"xx.xx.xx.xxxxxxxx.xx.xx.xx"
"......xx....xx....xx......"
"oxxxxxxxxxx.xx.xxxxxxxxxxo"
".xxxxxxxxxx.xx.xxxxxxxxxx."
".........................."
;

SandOrb2D::SandOrb2D()
	: Layer("SandOrb2D"), m_CameraController(1280.0f / 720.0f), m_SquareColor({ 0.4f, 0.8f, 0.8f, 1.0f })
{
}

void SandOrb2D::OnAttach()
{
	ORBE_PROFILE_FUNCTION();

	m_CheckerboardTexture = ORB::Texture2D::Create("assets/textures/Checkerboard.png");

	ORB::FramebufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
	m_Framebuffer = ORB::Framebuffer::Create(fbSpec);

	m_SpaceShooterTexture = ORB::Texture2D::Create("Game/Textures/SpaceShooterTextureAtlas.png");
	m_PacmanTexture = ORB::Texture2D::Create("Game/Textures/PacmanTextureAtlas.png");
	
	m_SpaceShipsSubTexture = ORB::SubTexture2D::CreateFromCoords(m_SpaceShooterTexture, { 817.0f, -6.0f - 768.0f }, { 614.0f, 768.0f });
	//m_ExplosionSubTexture = ORB::SubTexture2D::CreateFromCoords(m_SpaceShooterTexture, { 530.0f, -819.0f - 416.0f }, { 490.0f, 416.0f });
	//m_ExplosionSubTexture = ORB::SubTexture2D::CreateFromRECT(m_SpaceShooterTexture, { 530.0f, -819.0f - 416.0f, 490.0f, 416.0f });
	m_ExplosionSubTexture = ORB::SubTexture2D::CreateFromRECT_BL(m_SpaceShooterTexture, { 530.0f, 819.0f, 490.0f, 416.0f });

	m_PacmanSubTexture = ORB::SubTexture2D::CreateFromRECT_BL(m_PacmanTexture, { 352.0f, 0.0f, 32.0f, 32.0f });
	m_PacDotSubTexture = ORB::SubTexture2D::CreateFromRECT_BL(m_PacmanTexture, { 32.0f, 0.0f, 32.0f, 32.0f });
	
	// Pacman Texture Map
	m_GhostDeadSubTexture = ORB::SubTexture2D::CreateFromRECT_BL(m_PacmanTexture, { 128.0f, 0.0f, 32.0f, 32.0f });
	m_PacWorldSubTexture = ORB::SubTexture2D::CreateFromRECT_BL(m_PacmanTexture, { 0.0f, 32.0f, 1024.0f, 768.0f });

	m_PacmanMapWidth = s_PacmanMapWidth;
	m_PacmanMapHeight = (uint32_t)(strlen(s_PacmanMapTiles)) / s_PacmanMapWidth;

	m_PacmanTextureMap['.'] = ORB::SubTexture2D::CreateFromRECT_BL(m_PacmanTexture, {32.0f, 0.0f, 32.0f, 32.0f});
	m_PacmanTextureMap['o'] = ORB::SubTexture2D::CreateFromRECT_BL(m_PacmanTexture, {0.0f, 0.0f, 32.0f, 32.0f});
	m_PacmanTextureMap['p'] = ORB::SubTexture2D::CreateFromRECT_BL(m_PacmanTexture, { 352.0f, 0.0f, 32.0f, 32.0f });
	m_PacmanTextureMap[' '] = ORB::SubTexture2D::CreateFromRECT_BL(m_PacmanTexture, { 544.0f, 0.0f, 32.0f, 32.0f });
	m_PacmanTextureMap['-'] = ORB::SubTexture2D::CreateFromRECT_BL(m_PacmanTexture, { 544.0f, 0.0f, 32.0f, 32.0f });

	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 5.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };

	m_CameraController.SetZoomLevel(16.0f);
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
		m_Framebuffer->Bind();
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
		//for (float y = -5.0f; y < 5.0f; y += 1.0f)
		for (float y = -(float)(m_PacmanMapHeight / 2); y <= (float)(m_PacmanMapHeight / 2); y += 1.0f)
		{
			//for (float x = -5.0f; x < 5.0f; x += 1.0f)
			for (float x = -(float)(m_PacmanMapWidth / 2); x < (float)(m_PacmanMapWidth / 2); x += 1.0f)
			{
				//ORB::v4 color = { (x + 5.0f) / 10.0f, 0.3f, (y + 5.0f) / 10.0f, 0.7f };
				ORB::v4 color = { (x + m_PacmanMapWidth) / (m_PacmanMapWidth * 2), 0.3f, (y + m_PacmanMapHeight) / (m_PacmanMapHeight * 2), 0.7f };
				//ORB::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
				ORB::Renderer2D::DrawQuad({ x, y + 0.5f }, { 0.9f, 0.9f }, color);
			}
		}
		ORB::Renderer2D::EndScene();

		ORB::Renderer2D::BeginScene(m_CameraController.GetCamera());
		
		//ORB::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_SpaceShipsSubTexture);
		//ORB::Renderer2D::DrawQuad({ 1.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, m_ExplosionSubTexture);
		//ORB::Renderer2D::DrawQuad({ -1.0f, 0.0f, 0.5f }, { 0.5f, 0.5f }, m_PacmanSubTexture);
		//ORB::Renderer2D::DrawQuad({ -1.0f, 1.0f, 0.5f }, { 0.5f, 0.5f }, m_PacDotSubTexture);
		
		//ORB::Renderer2D::DrawQuad({ -0.5f, 0.5f, 0.4f }, { 46.0f, 35.0f }, m_PacWorldSubTexture);

		for (uint32_t y = 0; y < m_PacmanMapHeight; y++)
		{
			for (uint32_t x = 0; x < m_PacmanMapWidth; x++)
			{
				char tileType = s_PacmanMapTiles[x + y * m_PacmanMapWidth];
				ORB::Ref<ORB::SubTexture2D> subtexture;
				if (m_PacmanTextureMap.find(tileType) != m_PacmanTextureMap.end())
					subtexture = m_PacmanTextureMap[tileType];
				else
					subtexture = m_GhostDeadSubTexture;
				
				ORB::Renderer2D::DrawQuad({ x - m_PacmanMapWidth/2.0f, (m_PacmanMapHeight/2.0f) - y, 0.5f }, { 1.0f, 1.0f }, subtexture);
			}
		}

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
	m_Framebuffer->Unbind();
}

void SandOrb2D::OnImGuiRender()
{
	ORBE_PROFILE_FUNCTION();

	static bool dockspaceOpen = true;
	static bool opt_fullscreen = true;
	static bool opt_padding = false;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}
	else
	{
		dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
	// and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	if (!opt_padding)
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
	if (!opt_padding)
		ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// Submit the DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
				ORB::App::Get().Close();

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	ImGui::Begin("Settings");

	auto stats = ORB::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
	ImGui::Image((void*)textureID, ImVec2{ 1280.0f, 720.0f });
	ImGui::End();

	ImGui::End();
}

void SandOrb2D::OnEvent(ORB::Event& e)
{
	m_CameraController.OnEvent(e);
}
