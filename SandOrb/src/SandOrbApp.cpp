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
	SandOrb(ORB::AppCommandLineArgs args)
		: App("Sand Orb", args)
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new SandOrb2D());
	}
	~SandOrb() {}

};

ORB::App* ORB::CreateApplication(ORB::AppCommandLineArgs args)
{
	return new SandOrb(args);
}
