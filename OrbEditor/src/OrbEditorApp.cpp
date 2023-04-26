#include <OrbE.h>
#include <OrbE/Core/EntryPoint.h>

#include <ImGui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EditorLayer.h"

namespace ORB {

	class OrbEditor : public App
	{
	public:
		OrbEditor()
			: App("De Orb Editor")
		{
			PushLayer(new EditorLayer());
		}
		~OrbEditor() {}

	};

	App* CreateApplication()
	{
		return new OrbEditor();
	}
}