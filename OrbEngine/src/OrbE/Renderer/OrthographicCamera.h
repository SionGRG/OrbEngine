#pragma once

#include "OrbE/Math/Math.h"

namespace ORB {

	class OrthographicCamera
	{
	public: 
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		const v3& GetPosition() const { return m_Position; }
		void SetPosition(const v3& position) { m_Position = position; RecalculateViewMatrix(); }

		const float& GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const m4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const m4& GetViewMatrix() const { return m_ViewMatrix; }
		const m4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();
	private:
		m4 m_ProjectionMatrix;
		m4 m_ViewMatrix;
		m4 m_ViewProjectionMatrix;

		v3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;	// vertical rotation on the z-axis
	};
}
