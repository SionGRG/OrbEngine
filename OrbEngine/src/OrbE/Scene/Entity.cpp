#include "OrbPCH.h"
#include "OrbE/Scene/Entity.h"

namespace ORB {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}
}