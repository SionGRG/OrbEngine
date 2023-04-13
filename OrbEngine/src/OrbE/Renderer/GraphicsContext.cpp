#include "OrbPCH.h"
#include "OrbE/Renderer/GraphicsContext.h"

#include "OrbE/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace ORB {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				ORBE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		ORBE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}