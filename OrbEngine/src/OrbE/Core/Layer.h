#pragma once

#include "OrbE/Core/Base.h"
#include "OrbE/Events/Event.h"

#include "OrbE/Core/Timestep.h"

namespace ORB {

	class Layer
	{
	public:
		Layer(std::string_view name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		std::string_view GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}

