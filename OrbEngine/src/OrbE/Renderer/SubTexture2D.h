#pragma once

#include "OrbE/Maths/BasicMath.h"

#include "OrbE/Renderer/Texture.h"

namespace ORB {

	class SubTexture2D
	{
	public:
		SubTexture2D(const Ref<Texture2D>& texture, const v2& min, const v2& max);
	
		const Ref<Texture2D> GetTexture() const { return m_Texture; }
		const v2* GetTexCoords() const { return m_TexCoords; }

		static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D>& texture, const v2& coords, const v2 spriteSize);

	private:
		Ref<Texture2D> m_Texture;

		v2 m_TexCoords[4];
	};
}