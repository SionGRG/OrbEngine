#pragma once

#include "OrbE/Core/Layer.h"

#include "OrbE/Events/AppEvent.h"
#include "OrbE/Events/KeyEvent.h"
#include "OrbE/Events/MouseEvent.h"

namespace ORB {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}