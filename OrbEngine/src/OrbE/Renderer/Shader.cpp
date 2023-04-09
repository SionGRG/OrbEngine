#include "OrbPCH.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace ORB {

	Ref<Shader> Shader::Create(std::string_view filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ORBE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(filepath);
		}

		ORBE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ORBE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
		}

		ORBE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}