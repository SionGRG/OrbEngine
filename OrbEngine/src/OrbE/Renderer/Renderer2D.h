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

		// Primitives
		static void DrawQuad(const v2& position, const v2& size, const v4& color);
		static void DrawQuad(const v3& position, const v2& size, const v4& color);
		static void DrawQuad(const v2& position, const v2& size, const Ref<Texture2D>& texture);
		static void DrawQuad(const v3& position, const v2& size, const Ref<Texture2D>& texture);
	};
}