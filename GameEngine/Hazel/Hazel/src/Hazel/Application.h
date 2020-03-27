#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "Hazel/LayerStack.h"
#include "Hazel/ImGui/ImGuiLayer.h"


int main(int argc, char** argv);
namespace Hazel {

	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void OnEvent(Event& e);
		
		void PushLayer(Layer* layer);
		void PushOvelay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		void Run();
		bool OnWindowClose(WindowsCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);


		ImGuiLayer* m_ImGuiLayer;
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack; 
		float m_LastFrameTime = 0.0f;
		bool m_Minimized = false;

	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	//TO Be defined int client
	Application* CreateApplication();
}

