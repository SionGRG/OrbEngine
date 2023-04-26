#pragma once

#include <OrbE.h>

#include "ParticleSystem.h"

class SandOrb2D : public ORB::Layer
{
public:
	SandOrb2D();
	virtual ~SandOrb2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(ORB::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(ORB::Event& e) override;

private:
	ORB::OrthographicCameraController m_CameraController;
	
	// Temp
	ORB::Ref<ORB::VertexArray> m_SquareVA;
	ORB::Ref<ORB::Shader> m_FlatColorShader;
	ORB::Ref<ORB::Framebuffer> m_Framebuffer;

	ORB::Ref<ORB::Texture2D> m_CheckerboardTexture;
	ORB::Ref<ORB::Texture2D> m_SpaceShooterTexture;
	ORB::Ref<ORB::Texture2D> m_PacmanTexture;
	ORB::Ref<ORB::SubTexture2D> m_SpaceShipsSubTexture, m_ExplosionSubTexture;
	ORB::Ref<ORB::SubTexture2D> m_PacmanSubTexture, m_PacDotSubTexture, m_GhostDeadSubTexture, m_PacWorldSubTexture;

	ORB::v4 m_SquareColor = { 0.4f, 0.9f, 0.9f, 1.0f };

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;

	uint32_t m_PacmanMapWidth, m_PacmanMapHeight;
	std::unordered_map<char, ORB::Ref<ORB::SubTexture2D>> m_PacmanTextureMap;
};

