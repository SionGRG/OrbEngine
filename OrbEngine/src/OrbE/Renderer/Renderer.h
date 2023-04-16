#pragma once

#include "OrbE/Renderer/RenderCommand.h"
#include "OrbE/Renderer/OrthographicCamera.h"
#include "OrbE/Renderer/Shader.h"

namespace ORB {

	class Renderer
	{
	public:
		static void Init();
		static void Terminate();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(OrthographicCamera& camera); 
		static void EndScene(); 

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const m4& transform = m4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			m4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;
	};
}
