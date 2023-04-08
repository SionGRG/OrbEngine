#include "OrbPCH.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace ORB {

	Ref<Texture2D> Texture2D::Create(std::string_view path)
	{
		{
			switch (Renderer::GetAPI())
			{
			case RendererAPI::API::None:
				ORBE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLTexture2D>(path);
			}

			ORBE_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
}