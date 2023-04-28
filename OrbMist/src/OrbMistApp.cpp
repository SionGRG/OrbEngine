#include <OrbE.h>
#include <OrbE/Core/EntryPoint.h>

#include <ImGui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EditorLayer.h"

namespace ORB {

	class OrbMist : public App
	{
	public:
		OrbMist()
			: App("OrbMist")
		{
			PushLayer(new EditorLayer());
		}
		~OrbMist() {}

	};

	App* CreateApplication()
	{
		return new OrbMist();
	}
}