#pragma once

#include <entt.hpp>
#include "OrbE/Core/Timestep.h"

namespace ORB {

	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		// TEMP
		entt::registry& Reg() { return m_Registry; }

		void OnUpdate(Timestep ts);

	private:
		entt::registry m_Registry;
	};
}