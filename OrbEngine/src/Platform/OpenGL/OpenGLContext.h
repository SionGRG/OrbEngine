#pragma once

#include "OrbE/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace ORB {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};

}
