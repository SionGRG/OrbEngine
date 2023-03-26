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
		if (ORB::Input::IsKeyPressed(ORBE_KEY_TAB))
			ORBE_TRACE("Tab key is pressed (poll)!");
	}

	void OnEvent(ORB::Event& event) override
	{
		if (event.GetEventType() == ORB::EventType::KeyPressed)
		{
			ORB::KeyPressedEvent& e = (ORB::KeyPressedEvent&)event;
			if(e.GetKeyCode() == ORBE_KEY_TAB)
				ORBE_TRACE("Tab key is pressed (event)!");
			else
				ORBE_TRACE("{0}", (char)e.GetKeyCode());
		}
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