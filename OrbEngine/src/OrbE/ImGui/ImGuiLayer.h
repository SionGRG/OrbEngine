#pragma once

#include "OrbE/Layer.h"

#include "OrbE/Events/AppEvent.h"
#include "OrbE/Events/KeyEvent.h"
#include "OrbE/Events/MouseEvent.h"

namespace ORB {

	class ORBE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}