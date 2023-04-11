#pragma once

#include "OrbE/Renderer/Shader.h"
#include "OrbE/Maths/BasicMath.h"

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace ORB {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(std::string_view filepath);
		OpenGLShader(std::string_view name, std::string_view vertexSrc, std::string_view fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetFloat3(std::string_view name, const v3& value) override;
		virtual void SetFloat4(std::string_view name, const v4& value) override;
		virtual void SetMat4(std::string_view name, const m4& value) override;

		virtual const std::string_view GetName() const override { return m_Name; }


		void UploadUniformInt(std::string_view name, int value);
		
		void UploadUniformFloat(std::string_view name, float value);
		void UploadUniformFloat2(std::string_view name, const v2& value);
		void UploadUniformFloat3(std::string_view name, const v3& value);
		void UploadUniformFloat4(std::string_view name, const v4& value);

		void UploadUniformMat3(std::string_view name, const m3& matrix);
		void UploadUniformMat4(std::string_view name, const m4& matrix);

	private:
		std::string ReadFile(std::string_view filepath);
		std::unordered_map<GLenum, std::string> PreProcess(std::string_view source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

	private:
		uint32_t m_RenderID;
		std::string m_Name;
	};
}