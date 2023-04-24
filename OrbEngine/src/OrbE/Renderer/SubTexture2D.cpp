#include "OrbPCH.h"
#include "OrbE/Renderer/SubTexture2D.h"

namespace ORB {

	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const v2& min, const v2& max)
		: m_Texture(texture)
	{
		// Bottom left
		m_TexCoords[0] = { min.x, min.y };
		// Bottom right
		m_TexCoords[1] = { max.x, min.y };
		// top right
		m_TexCoords[2] = { max.x, max.y };
		// top left
		m_TexCoords[3] = { min.x, max.y };
	}

	Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& texture, const v2& coords, const v2 spriteSize)
	{
		/*
		constexpr float spriteWidth = 614.0f, spriteHeight = 768.0f;
		struct RECTF {
			float x = 817;
			float y = -6 - spriteHeight;
			float w = spriteWidth;
			float h = spriteHeight;
		} texDim;

		constexpr size_t quadVertexCount = 4;
		const v2 textureCoords[] = {
			// Bottom left
			{ (texDim.x) / sheetWidth,
			  (texDim.y) / sheetHeight },
			// Bottom right
			{ (texDim.x + texDim.w) / sheetWidth,
			  (texDim.y) / sheetHeight },
			// top right
			{ (texDim.x + texDim.w) / sheetWidth,
			  (texDim.y + texDim.h) / sheetHeight },
			// top left
			{ (texDim.x) / sheetWidth,
			  (texDim.y + texDim.h) / sheetHeight },
		};
		*/

		// Bottom left
		v2 min = { (coords.x) / texture->GetWidth(), (coords.y) / texture->GetHeight() };
		// top right
		v2 max = { (coords.x + spriteSize.x) / texture->GetWidth(), (coords.y + spriteSize.y) / texture->GetHeight() };

		return CreateRef<SubTexture2D>(texture, min, max);
	}

	Ref<SubTexture2D> SubTexture2D::CreateFromRECT(const Ref<Texture2D>& texture, const RECTF& rect)
	{
		// Bottom left
		v2 min = { (rect.x) / texture->GetWidth(), (rect.y) / texture->GetHeight() };
		// top right
		v2 max = { (rect.x + rect.width) / texture->GetWidth(), (rect.y + rect.height) / texture->GetHeight() };

		return CreateRef<SubTexture2D>(texture, min, max);
	}

	Ref<SubTexture2D> SubTexture2D::CreateFromRECT_BL(const Ref<Texture2D>& texture, const RECTF& rect)
	{
		// Bottom left
		v2 min = { (rect.x) / texture->GetWidth(), ((-rect.y - rect.height)) / texture->GetHeight() };
		// top right
		v2 max = { (rect.x + rect.width) / texture->GetWidth(), (-rect.y) / texture->GetHeight() };
		//v2 max = { (rect.x + rect.width) / texture->GetWidth(), ((-rect.y - rect.height) + rect.height) / texture->GetHeight() };

		return CreateRef<SubTexture2D>(texture, min, max);
	}
}