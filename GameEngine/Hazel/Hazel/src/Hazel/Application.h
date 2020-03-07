#pragma once
#include "Core.h"

namespace Hazel {

	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	//TO Be defined int client
	Application* CreateApplication();
}

