#include "SandOrb2D.h"
#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

SandOrb2D::SandOrb2D()
	: Layer("SandOrb2D"), m_CameraController(1280.0f / 720.0f)
{
}

void SandOrb2D::OnAttach()
{
	// Draw a square
	m_SquareVA = ORB::VertexArray::Create();

	float squareVertices[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	ORB::Ref<ORB::VertexBuffer> squareVB;
	squareVB = ORB::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

	squareVB->SetLayout({
		{ ORB::ShaderDataType::Float3, "a_Posision" }
	});

	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	ORB::Ref<ORB::IndexBuffer> squareIB;
	squareIB = ORB::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = ORB::Shader::Create("assets/shaders/FlatColor.glsl");
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

	ORB::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<ORB::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<ORB::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	ORB::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(ORB::m4(1.0f), ORB::v3(1.5f)));

	ORB::Renderer::EndScene();
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
