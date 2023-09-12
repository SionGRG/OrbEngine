#pragma once

#include "OrbE/Renderer/Camera.h"
#include "OrbE/Renderer/EditorCamera.h"
#include "OrbE/Renderer/OrthographicCamera.h"

#include "OrbE/Renderer/Texture.h"
#include "OrbE/Renderer/SubTexture2D.h"

#include "OrbE/Scene/Components.h"

namespace ORB {

	class Renderer2D
	{
	public:
		static void Init();
		static void Terminate();

		static void BeginScene(const Camera& camera, m4 transform);
		static void BeginScene(const EditorCamera& camera);
		static void BeginScene(const OrthographicCamera& camera); // TODO: Remove
		static void EndScene();
		static void Flush();

		/* Sprites */
		// Primitives
		static void DrawQuad(const v2& position, const v2& size, const v4& color);
		static void DrawQuad(const v3& position, const v2& size, const v4& color);
		static void DrawQuad(const v2& position, const v2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const v4& tintColor = v4(1.0f));
		static void DrawQuad(const v3& position, const v2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const v4& tintColor = v4(1.0f));
		static void DrawQuad(const v2& position, const v2& size, const Ref<SubTexture2D>& subtexture, float tilingFactor = 1.0f, const v4& tintColor = v4(1.0f));
		static void DrawQuad(const v3& position, const v2& size, const Ref<SubTexture2D>& subtexture, float tilingFactor = 1.0f, const v4& tintColor = v4(1.0f));

		// With Matrix transforms
		static void DrawQuad(const m4& transform, const v4& color, int entityID = -1);
		static void DrawQuad(const m4& transform, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const v4& tintColor = v4(1.0f), int entityID = -1);
		static void DrawQuad(const m4& transform, const Ref<SubTexture2D>& subtexture, float tilingFactor = 1.0f, const v4& tintColor = v4(1.0f), int entityID = -1);

		// Rotation is in radians
		static void DrawRotatedQuad(const v2& position, const v2& size, float rotation, const v4& color);
		static void DrawRotatedQuad(const v3& position, const v2& size, float rotation, const v4& color);
		static void DrawRotatedQuad(const v2& position, const v2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const v4& tintColor = v4(1.0f));
		static void DrawRotatedQuad(const v3& position, const v2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const v4& tintColor = v4(1.0f));
		static void DrawRotatedQuad(const v2& position, const v2& size, float rotation, const Ref<SubTexture2D>& subtexture, float tilingFactor = 1.0f, const v4& tintColor = v4(1.0f));
		static void DrawRotatedQuad(const v3& position, const v2& size, float rotation, const Ref<SubTexture2D>& subtexture, float tilingFactor = 1.0f, const v4& tintColor = v4(1.0f));

		// With sprite renderer component
		static void DrawSprite(const m4& transform, SpriteRendererComponent& src, int entityID);

		/* Circles */
		static void DrawCircle(const m4& transform, const v4& color, float thickness = 1.0f, float fade = 0.005f, int entityID = -1);
		
		/* Lines */
		static void DrawLine(const v3& p0, const v3& p1, const v4& color, int entityID = -1);
		
		static float GetLineWidth();
		static void SetLineWidth(float width);
		
		/* Poly Lines */
		static void DrawPolyLine(const m4& transform, const v3& p0, const v3& p1, const v4& color, float thickness, int entityID = -1);
		
		/* Rects */
		static void DrawRect(const v3& position, const v2& size, const v4& color, int entityID = -1);
		static void DrawRect(const m4& transform, const v4& color, int entityID = -1);

		// Stats
		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;
			uint32_t CircleCount = 0;
			uint32_t PolyLineCount = 0;

			uint32_t GetTotalVertexCount() const { return (QuadCount + CircleCount + PolyLineCount) * 4; }
			uint32_t GetTotalIndexCount() const { return (QuadCount + CircleCount + PolyLineCount) * 6; }
		};

		static void ResetStats();
		static Statistics GetStats();

	private:
		static void StartBatch();
		static void NextBatch();
	};
}
