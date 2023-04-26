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
	SandOrb()
		: App("Sand Orb")
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new SandOrb2D());
	}
	~SandOrb() {}

};

ORB::App* ORB::CreateApplication()
{
	return new SandOrb();
}