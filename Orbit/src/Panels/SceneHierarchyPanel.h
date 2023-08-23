#pragma once

#include "OrbE/Core/Base.h"
#include "OrbE/Scene/Scene.h"
#include "OrbE/Scene/Entity.h"

namespace ORB {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender();

		Entity GetSelectedEntity() const { return m_SelectionContext; }
		void SetSelectedEntity(Entity entity);

	private:
		template<typename T>
		void DisplayAddComponentEntry(std::string_view entryName);

		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);

	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}
