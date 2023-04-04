#include "OrbPCH.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace ORB {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		ORBE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ORBE_CORE_ASSERT(status, "Failed to initialize Glad!");

		// Print the GPU Details to the console
		ORBE_CORE_INFO("OpenGL Info:");
		ORBE_CORE_INFO("  Vendor:	{0}", (char*)glGetString(GL_VENDOR));
		ORBE_CORE_INFO("  Renderer:	{0}", (char*)glGetString(GL_RENDERER));
		ORBE_CORE_INFO("  Version:	{0}", (char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}