#include "OrbE.h"

class ExampleLayer : public ORB::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		ORBE_INFO("ExampleLayer::Update");
	}

	void OnEvent(ORB::Event& event) override
	{
		ORBE_TRACE("{0}", event);
	}
};


class SandOrb : public ORB::App
{
public:
	SandOrb() 
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new ORB::ImGuiLayer());
	}
	~SandOrb() {}

};

ORB::App* ORB::CreateApplication()
{
	return new SandOrb();
}