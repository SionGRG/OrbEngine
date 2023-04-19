#pragma once

#include "OrbE/Renderer/OrthographicCamera.h"
#include "OrbE/Renderer/Texture.h"

namespace ORB {

	class Renderer2D
	{
	public:
		static void Init();
		static void Terminate();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		// Primitives
		static void DrawQuad(const v2& position, const v2& size, const v4& color);
		static void DrawQuad(const v3& position, const v2& size, const v4& color);
		static void DrawQuad(const v2& position, const v2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const v4& tintColor = v4(1.0f));
		static void DrawQuad(const v3& position, const v2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const v4& tintColor = v4(1.0f));

		static void DrawRotatedQuad(const v2& position, const v2& size, float rotation, const v4& color);
		static void DrawRotatedQuad(const v3& position, const v2& size, float rotation, const v4& color);
		static void DrawRotatedQuad(const v2& position, const v2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const v4& tintColor = v4(1.0f));
		static void DrawRotatedQuad(const v3& position, const v2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const v4& tintColor = v4(1.0f));

	};
}