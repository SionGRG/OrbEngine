#pragma once

#include "OrbE.h"

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

	ORB::v4 m_SquareColor = { 0.4f, 0.9f, 0.9f, 1.0f };
};

