#include "OrbPCH.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace ORB {

	struct Renderer2DStorage
	{
		Ref<VertexArray>      QuadVertexArray;
		Ref<Shader>           FlatColorShader;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage();

		// Draw a square
		s_Data->QuadVertexArray = VertexArray::Create();

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Ref<VertexBuffer> squareVB;
		squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Posision" }
			});

		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB;
		squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

		s_Data->FlatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");
	}

	void Renderer2D::Terminate()
	{
		delete s_Data;
	}
	
	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}
	
	void Renderer2D::EndScene()
	{
	}
	
	void Renderer2D::DrawQuad(const v2& position, const v2& size, const v4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f}, size, color);
	}
	
	void Renderer2D::DrawQuad(const v3& position, const v2& size, const v4& color)
	{
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetFloat4("u_Color", color);

		m4 transform =  glm::translate(m4(1.0f), position) * /* rotation * */ glm::scale(m4(1.0f), {size.x, size.y, 1.0f});
		s_Data->FlatColorShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}