#include <OrbE.h>

#include "ImGui/imgui.h"

class ExampleLayer : public ORB::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f * 1.5, 1.6f * 1.5, -0.9f * 1.5, 0.9f * 1.5), m_CameraPosition(0.0f)
	{
		// Draw a triangle
		m_VertexArray.reset(ORB::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.9f, 0.6f, 0.1f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.8f, 0.1f, 0.1f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.4f, 0.9f, 0.9f, 1.0f
		};

		std::shared_ptr<ORB::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(ORB::VertexBuffer::Create(vertices, sizeof(vertices)));

		ORB::BufferLayout layout = {
			{ ORB::ShaderDataType::Float3, "a_Posision"},
			{ ORB::ShaderDataType::Float4, "a_Color"}
			//{ ShaderDataType::Float3, "a_Normal"}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<ORB::IndexBuffer> indexBuffer;
		indexBuffer.reset(ORB::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// Draw a square
		m_SquareVA.reset(ORB::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<ORB::VertexBuffer> squareVB;
		squareVB.reset(ORB::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ ORB::ShaderDataType::Float3, "a_Posision"},
			//{ ShaderDataType::Float4, "a_Color"}
			//{ ShaderDataType::Float3, "a_Normal"}
			});

		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<ORB::IndexBuffer> squareIB;
		squareIB.reset(ORB::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		m_SquareVA->SetIndexBuffer(squareIB);

		// Shaders for the triangle
		std::string vertexSrc = R"(
			#version 330 core
 
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}		
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 o_Color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				o_Color = v_Color;
			}
		
		)";

		m_Shader.reset(new ORB::Shader(vertexSrc, fragmentSrc));

		// Shaders for the square
		std::string squareShaderVertexSrc = R"(
			#version 330 core
 
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}		
		)";

		std::string squareShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 o_Color;

			in vec3 v_Position;

			void main()
			{
				o_Color = vec4(0.1, 0.6, 0.6, 1.0);
			}
		
		)";

		m_SquareShader.reset(new ORB::Shader(squareShaderVertexSrc, squareShaderFragmentSrc));
	}

	void OnUpdate(ORB::Timestep ts) override
	{
		// Camera Movement
		if (ORB::Input::IsKeyPressed(ORBE_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (ORB::Input::IsKeyPressed(ORBE_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (ORB::Input::IsKeyPressed(ORBE_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		else if (ORB::Input::IsKeyPressed(ORBE_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;

		// Camera Rotation
		if (ORB::Input::IsKeyPressed(ORBE_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (ORB::Input::IsKeyPressed(ORBE_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;


		ORB::RenderCommand::SetClearColor({ 0.15f, 0.15f, 0.15f, 1.0f });
		ORB::RenderCommand::Clear();

		ORB::Renderer::BeginScene(m_Camera);

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		ORB::Renderer::Submit(m_SquareShader, m_SquareVA);	// Draw square
		ORB::Renderer::Submit(m_Shader, m_VertexArray);		// Draw Triangle

		ORB:: Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
	}

	void OnEvent(ORB::Event& event) override
	{
	}

private:
	std::shared_ptr<ORB::Shader> m_Shader;
	std::shared_ptr<ORB::VertexArray> m_VertexArray;

	std::shared_ptr<ORB::Shader> m_SquareShader;
	std::shared_ptr<ORB::VertexArray> m_SquareVA;

	ORB::OrthographicCamera m_Camera;
	ORB::v3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 120.0f;
};


class SandOrb : public ORB::App
{
public:
	SandOrb() 
	{
		PushLayer(new ExampleLayer());
	}
	~SandOrb() {}

};

ORB::App* ORB::CreateApplication()
{
	return new SandOrb();
}