#include "hzpch.h"

#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"
namespace Hazel {
	Application::Application()
	{
	}

	Application::~Application()
	{
	}
	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			HZ_TRACE(e.ToString());
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			HZ_TRACE(e.ToString());
		}
		
		while (true);
	}
}
