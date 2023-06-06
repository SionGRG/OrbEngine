#pragma once

#include "OrbE/Renderer/Camera.h"
#include "OrbE/Core/Timestep.h"
#include "OrbE/Events/Event.h"
#include "OrbE/Events/MouseEvent.h"
#include "OrbE/Math/Math.h"

namespace ORB {

	class EditorCamera : public Camera
	{
	public:
		EditorCamera() = default;
		EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		inline float GetDistance() const { return m_Distance; }
		inline void SetDistance(float distance) { m_Distance = distance; }

		inline void SetViewport(float width, float height) { m_ViewportWidth = width; m_ViewportHeight = height; UpdateProjection(); }

		const m4& GetViewMatrix() const { return m_ViewMatrix; }
		m4 GetViewProjection() const { return m_Projection * m_ViewMatrix; }

		v3 GetUpDirection() const;
		v3 GetRightDirection() const;
		v3 GetForwardDirection() const;
		const v3& GetPosition() const { return m_Position; }
		q4 GetOrientation() const;

		float GetPitch() const { return m_Pitch; }
		float GetYaw() const { return m_Yaw; }

	private:
		void UpdateProjection();
		void UpdateView();

		bool OnMouseScroll(MouseScrolledEvent& e);

		void MousePan(const v2& delta);
		void MouseRotate(const v2& delta);
		void MouseZoom(float delta);

		v3 CalculatePosition() const;

		std::pair<float, float> PanSpeed() const;
		float RotationSpeed() const;
		float ZoomSpeed() const;

	private:
		float m_FOV = 45.0f, m_AspectRatio = 1.778f, m_NearClip = 0.1f, m_FarClip = 1000.0f;
		
		m4 m_ViewMatrix = m4(1.0f);
		v3 m_Position = { 0.0f, 0.0f, 0.0f };
		v3 m_FocalPoint = { 0.0f, 0.0f, 0.0f };

		v2 m_InitialMousePosition = { 0.0f, 0.0f };

		float m_Distance = 10.0f;
		float m_Pitch = 0.0f, m_Yaw = 0.0f;

		float m_ViewportWidth = 1280.0f, m_ViewportHeight = 720.0f;
	};
}
