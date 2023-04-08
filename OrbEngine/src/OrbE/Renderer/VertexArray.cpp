#include "OrbPCH.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace ORB {
	
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ORBE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		}

		ORBE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}