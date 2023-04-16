#pragma once

#include "OrbE.h"

class ExampleLayer : public ORB::Layer
{
public:
	ExampleLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(ORB::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(ORB::Event& e) override;

private:
	ORB::ShaderLibrary m_ShaderLibrary;
	ORB::Ref<ORB::Shader> m_Shader;
	ORB::Ref<ORB::VertexArray> m_VertexArray;

	ORB::Ref<ORB::Shader> m_SquareShader;
	ORB::Ref<ORB::VertexArray> m_SquareVA;

	ORB::Ref<ORB::Texture2D> m_Texture, m_DeOrbLogoTexture;

	ORB::OrthographicCameraController m_CameraController;

	ORB::v3 m_TrianglePosition;
	float m_TriangleMoveSpeed = 1.0f;

	ORB::v3 m_SquareColor = { 0.4f, 0.9f, 0.9f };
};
