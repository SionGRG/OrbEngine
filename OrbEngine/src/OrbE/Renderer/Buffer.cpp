#include "OrbPCH.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace ORB {

	// =====================================================================
	// Vertex Buffer class
	// =====================================================================
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: 
				ORBE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		ORBE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	// =====================================================================
	// Index Buffer class
	// =====================================================================
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				ORBE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLIndexBuffer>(indices, size);
		}

		ORBE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}