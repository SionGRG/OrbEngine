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
		Orbit(AppSpecification specification)
			: App(specification)
		{
			PushLayer(new EditorLayer());
		}
		~Orbit() {}

	};

	App* CreateApplication(AppCommandLineArgs args)
	{
		AppSpecification spec;
		spec.Name = "Orbit";
		spec.WorkingDirectory = "../Orbit";
		spec.CommandLineArgs = args;

		return new Orbit(spec);
	}
}
