#include "OrbPCH.h"
#include "OrbE/Renderer/Renderer2D.h"

#include "OrbE/Renderer/VertexArray.h"
#include "OrbE/Renderer/Shader.h"
#include "OrbE/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace ORB {

	struct QuadVertex
	{
		v3 Position;
		v4 Color;
		v2 TexCoord;
		// TODO: texid, maskid
	};

	struct Renderer2DData
	{
		const uint32_t        MaxQuads = 10000;
		const uint32_t        MaxVertices = MaxQuads * 4;
		const uint32_t        MaxIndices = MaxQuads * 6;

		Ref<VertexArray>      QuadVertexArray;
		Ref<VertexBuffer>      QuadVertexBuffer;
		Ref<Shader>           TextureShader;
		Ref<Texture2D>        WhiteTexture;

		uint32_t              QuadIndexCount = 0;
		QuadVertex*           QuadVertexBufferBase = nullptr;
		QuadVertex*           QuadVertexBufferPtr = nullptr;
	};

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		ORBE_PROFILE_FUNCTION();

		// Draw a Quad
		s_Data.QuadVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Posision" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" }
			});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;

		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		s_Data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Terminate()
	{
		ORBE_PROFILE_FUNCTION();
	}
	
	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		ORBE_PROFILE_FUNCTION();
		
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
	}
	
	void Renderer2D::EndScene()
	{
		ORBE_PROFILE_FUNCTION();
		
		uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);
	
		Flush();
	}

	void Renderer2D::Flush()
	{
		ORBE_PROFILE_FUNCTION();

		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
	}
	
	void Renderer2D::DrawQuad(const v2& position, const v2& size, const v4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f}, size, color);
	}
	
	void Renderer2D::DrawQuad(const v3& position, const v2& size, const v4& color)
	{
		ORBE_PROFILE_FUNCTION();

		s_Data.QuadVertexBufferPtr->Position = position;
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, 0.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferPtr++;
		
		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferPtr++;
		
		s_Data.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, 0.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferPtr++;
		
		s_Data.QuadIndexCount += 6;

		/*
		s_Data.TextureShader->SetFloat4("u_Color", color);
		s_Data.TextureShader->SetFloat("u_TilingFactor", 1.0f);
		s_Data.WhiteTexture->Bind();

		m4 transform =  glm::translate(m4(1.0f), position) 
			* glm::scale(m4(1.0f), {size.x, size.y, 1.0f});
		s_Data.TextureShader->SetMat4("u_Transform", transform);
		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
		*/
	}
	
	void Renderer2D::DrawQuad(const v2& position, const v2& size, const Ref<Texture2D>& texture, float tilingFactor, const v4& tintColor)
	{
		DrawQuad({ position.x, position.y, 0.0f}, size, texture, tilingFactor, tintColor);
	}
	
	void Renderer2D::DrawQuad(const v3& position, const v2& size, const Ref<Texture2D>& texture, float tilingFactor, const v4& tintColor)
	{
		ORBE_PROFILE_FUNCTION();
		
		s_Data.TextureShader->SetFloat4("u_Color", tintColor);
		s_Data.TextureShader->SetFloat("u_TilingFactor", tilingFactor);
		texture->Bind();

		m4 transform = glm::translate(m4(1.0f), position) 
			* glm::scale(m4(1.0f), { size.x, size.y, 1.0f });
		s_Data.TextureShader->SetMat4("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const v2& position, const v2& size, float rotation, const v4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}
	
	void Renderer2D::DrawRotatedQuad(const v3& position, const v2& size, float rotation, const v4& color)
	{
		ORBE_PROFILE_FUNCTION();

		s_Data.TextureShader->SetFloat4("u_Color", color);
		s_Data.TextureShader->SetFloat("u_TilingFactor", 1.0f);
		s_Data.WhiteTexture->Bind();

		m4 transform = glm::translate(m4(1.0f), position) 
			* glm::rotate(m4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(m4(1.0f), { size.x, size.y, 1.0f });
		s_Data.TextureShader->SetMat4("u_Transform", transform);
		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
	}
	
	void Renderer2D::DrawRotatedQuad(const v2& position, const v2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const v4& tintColor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f}, size, rotation, texture, tilingFactor, tintColor);
	}
	
	void Renderer2D::DrawRotatedQuad(const v3& position, const v2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const v4& tintColor)
	{
		ORBE_PROFILE_FUNCTION();

		s_Data.TextureShader->SetFloat4("u_Color", tintColor);
		s_Data.TextureShader->SetFloat("u_TilingFactor", tilingFactor);
		texture->Bind();

		m4 transform = glm::translate(m4(1.0f), position) 
			* glm::rotate(m4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(m4(1.0f), { size.x, size.y, 1.0f });
		s_Data.TextureShader->SetMat4("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
	}

}