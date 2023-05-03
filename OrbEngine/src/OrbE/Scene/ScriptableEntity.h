#pragma once

#include "OrbE/Scene/Entity.h"

namespace ORB {

	class ScriptableEntity : public Entity
	{
	public:
		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}

	private:
		Entity m_Entity;
		friend class Scene;
	};
}