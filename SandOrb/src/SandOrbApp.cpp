#include <OrbE.h>

#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public ORB::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f * 1.5, 1.6f * 1.5, -0.9f * 1.5, 0.9f * 1.5), m_CameraPosition(0.0f), m_TrianglePosition(0.0f)
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
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
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
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}		
		)";

		std::string squareShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 o_Color;

			in vec3 v_Position;

			uniform vec4 u_Color;

			void main()
			{
				o_Color = u_Color;
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

		// Triangle Position Movement controls
		if (ORB::Input::IsKeyPressed(ORBE_KEY_J))
			m_TrianglePosition.x -= m_TriangleMoveSpeed * ts;
		else if (ORB::Input::IsKeyPressed(ORBE_KEY_L))
			m_TrianglePosition.x += m_TriangleMoveSpeed * ts;

		if (ORB::Input::IsKeyPressed(ORBE_KEY_K))
			m_TrianglePosition.y -= m_TriangleMoveSpeed * ts;
		else if (ORB::Input::IsKeyPressed(ORBE_KEY_I))
			m_TrianglePosition.y += m_TriangleMoveSpeed * ts;

		ORB::RenderCommand::SetClearColor({ 0.15f, 0.15f, 0.15f, 1.0f });
		ORB::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		ORB::Renderer::BeginScene(m_Camera);

		static ORB::m4 squareScale = glm::scale(ORB::m4(1.0f), ORB::v3(0.1f));

		ORB::v4 grayColor(0.4f, 0.4f, 0.4f, 1.0f);
		ORB::v4 whiteColor(0.9f, 0.9f, 0.9f, 1.0f);
		ORB::v4 cyanColor(0.2f, 0.8f, 0.8f, 1.0f);
		ORB::v4 redColor(0.8f, 0.3f, 0.2f, 1.0f);
		ORB::v4 blueColor(0.2f, 0.3f, 0.6f, 1.0f);

		// ORB::MaterialRef material = new ORB::Material(m_SquareShader);
		// ORB::MaterialInstanceRef m1 = new ORB::MaterialInstance(material);

		// material->Set("u_Color", grayColor);
		// material->SetTexture("u_AlbedoMap", texture);
		// squareMesh->SetMaterial(m1);

		for (int y = -10; y < 10; y++)
		{
			for (int x = -10; x < 10; x++)
			{
				ORB::v3 pos(x * 0.11f, y * 0.11f, 0.0f);
				ORB::m4 squareTransform = glm::translate(ORB::m4(1.0f), pos) * squareScale;
				
				// Set alternating colours
				if (x % 2 == 0)
				{
					if ((y > -7 && y < 7) && (x > -7 && x < 7))
						m_SquareShader->UploadUniformFloat4("u_Color", cyanColor);
					else
						m_SquareShader->UploadUniformFloat4("u_Color", grayColor);
				}
				else
				{
					if ((y > -7 && y < 7) && (x > -7 && x < 7))
						m_SquareShader->UploadUniformFloat4("u_Color", blueColor);
					else
						m_SquareShader->UploadUniformFloat4("u_Color", whiteColor);
				}

				ORB::Renderer::Submit(m_SquareShader, m_SquareVA, squareTransform);		// Draw squares
				// ORB::Renderer::Submit(m1, m_SquareVA, squareTransform);		// Draw squares with a material
			}
		}

		ORB::m4 triangleTransform = glm::translate(ORB::m4(1.0f), m_TrianglePosition);
		ORB::Renderer::Submit(m_Shader, m_VertexArray, triangleTransform);		// Draw Triangle

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
	
	ORB::v3 m_TrianglePosition;
	float m_TriangleMoveSpeed = 1.0f;
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