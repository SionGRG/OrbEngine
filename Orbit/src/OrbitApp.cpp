#include <OrbE.h>
#include <OrbE/Core/EntryPoint.h>

#include <ImGui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EditorLayer.h"

namespace ORB {

	class Orbit : public App
	{
	public:
		Orbit(AppCommandLineArgs args)
			: App("Orbit", args)
		{
			PushLayer(new EditorLayer());
		}
		~Orbit() {}

	};

	App* CreateApplication(AppCommandLineArgs args)
	{
		return new Orbit(args);
	}
}
