#include "OrbPCH.h"
#include "OrthographicCameraController.h"

#include "OrbE/Core/Input.h"
#include "OrbE/Core/KeyCodes.h"

namespace ORB {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}
	
	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		// Camera Movement
		if (Input::IsKeyPressed(ORBE_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(ORBE_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;

		if (Input::IsKeyPressed(ORBE_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(ORBE_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;

		// Camera Rotation, which is optional
		if (m_Rotation)
		{
			if (Input::IsKeyPressed(ORBE_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			else if (Input::IsKeyPressed(ORBE_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;
			
			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}
	
	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(ORBE_BIND_EVENT_FN(OrthographicCameraController::onMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(ORBE_BIND_EVENT_FN(OrthographicCameraController::onWindowResized));
	}
	
	bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}
	
	bool OrthographicCameraController::onWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight() ;
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}
}