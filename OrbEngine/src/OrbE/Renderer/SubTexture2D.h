#pragma once

#include "OrbE/Math/Math.h"
#include "OrbE/Utils/RectDefs.h"

#include "OrbE/Renderer/Texture.h"

namespace ORB {

	class SubTexture2D
	{
	public:
		SubTexture2D(const Ref<Texture2D>& texture, const v2& min, const v2& max);
	
		const Ref<Texture2D> GetTexture() const { return m_Texture; }
		const v2* GetTexCoords() const { return m_TexCoords; }

		static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D>& texture, const v2& coords, const v2 spriteSize);
		
		// Create a SubTexture with the rect's position coordinates being the Top-Left vertex of the rectangle
		static Ref<SubTexture2D> CreateFromRECT(const Ref<Texture2D>& texture, const RECTF& rect);
		
		// Create a SubTexture with the rect's position coordinates being the Bottom-Left vertex of the rectangle
		static Ref<SubTexture2D> CreateFromRECT_BL(const Ref<Texture2D>& texture, const RECTF& rect);

	private:
		Ref<Texture2D> m_Texture;

		v2 m_TexCoords[4];
	};
}
