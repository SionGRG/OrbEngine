#include <OrbE.h>
#include <OrbE/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SandOrb2D.h"

class ExampleLayer : public ORB::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f), m_TrianglePosition(0.0f)
	{
		// Draw a triangle
		m_VertexArray = ORB::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.9f, 0.6f, 0.1f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.8f, 0.1f, 0.1f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.4f, 0.9f, 0.9f, 1.0f
		};

		ORB::Ref<ORB::VertexBuffer> vertexBuffer;
		vertexBuffer = ORB::VertexBuffer::Create(vertices, sizeof(vertices));

		ORB::BufferLayout layout = {
			{ ORB::ShaderDataType::Float3, "a_Posision"},
			{ ORB::ShaderDataType::Float4, "a_Color"}
			//{ ShaderDataType::Float3, "a_Normal"}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		ORB::Ref<ORB::IndexBuffer> indexBuffer;
		indexBuffer = ORB::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// Draw a square
		m_SquareVA = ORB::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		ORB::Ref<ORB::VertexBuffer> squareVB;
		squareVB = ORB::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		squareVB->SetLayout({
			{ ORB::ShaderDataType::Float3, "a_Posision"},
			{ ORB::ShaderDataType::Float2, "a_TexCoord"}
			//{ ORB::ShaderDataType::Float4, "a_Color"}
			//{ ORB::ShaderDataType::Float3, "a_Normal"}
			});

		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		ORB::Ref<ORB::IndexBuffer> squareIB;
		squareIB = ORB::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

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

		m_Shader = ORB::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

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

			uniform vec3 u_Color;

			void main()
			{
				o_Color = vec4(u_Color, 1.0);
			}
		
		)";

		m_SquareShader = ORB::Shader::Create("SquareColor", squareShaderVertexSrc, squareShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = ORB::Texture2D::Create("assets/textures/Checkerboard.png");
		m_DeOrbLogoTexture = ORB::Texture2D::Create("assets/textures/DeOrb_Logo.png");
		
		std::dynamic_pointer_cast<ORB::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<ORB::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(ORB::Timestep ts) override
	{
		// Update --------------------------------------------------------------
		m_CameraController.OnUpdate(ts);

		// Triangle Position Movement controls
		if (ORB::Input::IsKeyPressed(ORBE_KEY_J))
			m_TrianglePosition.x -= m_TriangleMoveSpeed * ts;
		else if (ORB::Input::IsKeyPressed(ORBE_KEY_L))
			m_TrianglePosition.x += m_TriangleMoveSpeed * ts;

		if (ORB::Input::IsKeyPressed(ORBE_KEY_K))
			m_TrianglePosition.y -= m_TriangleMoveSpeed * ts;
		else if (ORB::Input::IsKeyPressed(ORBE_KEY_I))
			m_TrianglePosition.y += m_TriangleMoveSpeed * ts;

		// Render --------------------------------------------------------------
		ORB::RenderCommand::SetClearColor({ 0.15f, 0.15f, 0.15f, 1.0f });
		ORB::RenderCommand::Clear();

		ORB::Renderer::BeginScene(m_CameraController.GetCamera());

		static ORB::m4 squareScale = glm::scale(ORB::m4(1.0f), ORB::v3(0.1f));

		// ORB::MaterialRef material = new ORB::Material(m_SquareShader);
		// ORB::MaterialInstanceRef m1 = new ORB::MaterialInstance(material);

		// material->Set("u_Color", grayColor);
		// material->SetTexture("u_AlbedoMap", texture);
		// squareMesh->SetMaterial(m1);
		
		std::dynamic_pointer_cast<ORB::OpenGLShader>(m_SquareShader)->Bind();
		std::dynamic_pointer_cast<ORB::OpenGLShader>(m_SquareShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = -10; y < 10; y++)
		{
			for (int x = -10; x < 10; x++)
			{
				ORB::v3 pos(x * 0.11f, y * 0.11f, 0.0f);
				ORB::m4 squareTransform = glm::translate(ORB::m4(1.0f), pos) * squareScale;
				ORB::Renderer::Submit(m_SquareShader, m_SquareVA, squareTransform);		// Draw squares
				
				// ORB::Renderer::Submit(m1, m_SquareVA, squareTransform);		// Draw squares with a material
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");
		
		// Draw a textured square 
		m_Texture->Bind();		// Bind the square texture
		ORB::Renderer::Submit(textureShader, m_SquareVA, glm::scale(ORB::m4(1.0f), ORB::v3(1.5f)));
		
		// Draw DeOrb Logo Texture
		m_DeOrbLogoTexture->Bind();		// Bind the square texture
		ORB::Renderer::Submit(textureShader, m_SquareVA, glm::scale(ORB::m4(1.0f), ORB::v3(1.5f)));

		// Draw Triangle
		ORB::m4 triangleTransform = glm::translate(ORB::m4(1.0f), m_TrianglePosition);
		//ORB::Renderer::Submit(m_Shader, m_VertexArray, triangleTransform);

		ORB:: Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(ORB::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

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


class SandOrb : public ORB::App
{
public:
	SandOrb() 
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new SandOrb2D());
	}
	~SandOrb() {}

};

ORB::App* ORB::CreateApplication()
{
	return new SandOrb();
}