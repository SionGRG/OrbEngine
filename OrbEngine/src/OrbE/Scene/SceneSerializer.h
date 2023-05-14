#pragma once

#include "OrbE/Scene/Scene.h"

namespace ORB {

	class SceneSerializer
	{
	public:
		SceneSerializer(const Ref<Scene>& scene);

		void Serialize(std::string_view filepath);          // Serialize to text
		void SerializeRuntime(std::string_view filepath);   // Serialize to Binary

		bool Deserialize(std::string_view filepath);          // Deserialize to text
		bool DeserializeRuntime(std::string_view filepath);   // Deserialize to Binary

	private:
		Ref<Scene> m_Scene;
	};
}
