#include "Hazel.h"

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		HZ_INFO("ExampleLayer::Update");
	}

	void OnEvent(Hazel::Event& event) 
	{
		HZ_TRACE("Event");
	}
};



class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOvelay(new Hazel::ImGuiLayer());
	};
	~Sandbox()
	{

	}
};
Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}