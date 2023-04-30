#pragma once

#include <entt.hpp>
#include "OrbE/Core/Timestep.h"

namespace ORB {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(std::string_view name = "");

		void OnUpdate(Timestep ts);

	private:
		entt::registry m_Registry;

		friend class Entity;
	};
}