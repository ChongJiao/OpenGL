#pragma once
#include "Hazel/Renderer/GraphicsContext.h"

struct GLFWwindow;
namespace Hazel
{
	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}