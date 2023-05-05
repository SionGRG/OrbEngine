#include "OrbPCH.h"
#include "Platform/OpenGL/OpenGLContext.h"

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
		ORBE_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ORBE_CORE_ASSERT(status, "Failed to initialize Glad!");

		// Print the GPU Details to the console
		ORBE_CORE_INFO(" ============== OpenGL Info: ============== ");
		ORBE_CORE_INFO("  Vendor:	{0}", (char*)glGetString(GL_VENDOR));
		ORBE_CORE_INFO("  Renderer:	{0}", (char*)glGetString(GL_RENDERER));
		ORBE_CORE_INFO("  Version:	{0}", (char*)glGetString(GL_VERSION));

		// Check the OpenGL version
		ORBE_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major== 4 && GLVersion.minor>= 5), "De Orb Engine requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		ORBE_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}