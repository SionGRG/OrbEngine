#pragma once

#include <OrbE.h>

namespace ORB {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;

	private:
		OrthographicCameraController m_CameraController;
	
		// Temp
		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;
		entt::entity m_SquareEntity;

		Ref<Texture2D> m_CheckerboardTexture;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		v2 m_ViewportSize = { 0.0f, 0.0f };

		v4 m_SquareColor = { 0.4f, 0.9f, 0.9f, 1.0f };
	};
}