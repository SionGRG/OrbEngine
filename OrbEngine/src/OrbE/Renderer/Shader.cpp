#include "OrbPCH.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace ORB {

	// =====================================================================
	// Shader class
	// =====================================================================
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

	Ref<Shader> Shader::Create(std::string_view name, std::string_view vertexSrc, std::string_view fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ORBE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		ORBE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	// =====================================================================
	// Shader Library class
	// =====================================================================
	void ShaderLibrary::Add(std::string_view name, const Ref<Shader>& shader)
	{
		ORBE_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name.data()] = shader;
	}
	
	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		ORBE_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name.data()] = shader;
	}
	
	Ref<Shader> ShaderLibrary::Load(std::string_view name, std::string_view filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}
	
	Ref<Shader> ShaderLibrary::Load(std::string_view filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}
	
	Ref<Shader> ShaderLibrary::Get(std::string_view name)
	{
		ORBE_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name.data()];
	}
	
	bool ShaderLibrary::Exists(std::string_view name) const
	{
		return m_Shaders.find(name.data()) != m_Shaders.end();
	}
}