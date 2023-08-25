#include <OrbE.h>
#include <OrbE/Core/EntryPoint.h>

#include <ImGui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ExampleLayer.h"
#include "SandOrb2D.h"

class SandOrb : public ORB::App
{
public:
	SandOrb(const ORB::AppSpecification& specification)
		: App(specification)
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new SandOrb2D());
	}
	~SandOrb() {}

};

ORB::App* ORB::CreateApplication(ORB::AppCommandLineArgs args)
{
	AppSpecification spec;
	spec.Name = "Sand Orb";
	spec.WorkingDirectory = "../Orbit";
	spec.CommandLineArgs = args;
	
	return new SandOrb(spec);
}
