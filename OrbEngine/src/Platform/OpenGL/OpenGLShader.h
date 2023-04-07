#pragma once

#include "OrbE/Renderer/Shader.h"
#include "OrbE/Maths/BasicMath.h"

namespace ORB {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UploadUniformInt(std::string_view name, int value);
		
		void UploadUniformFloat(std::string_view name, float value);
		void UploadUniformFloat2(std::string_view name, const v2& value);
		void UploadUniformFloat3(std::string_view name, const v3& value);
		void UploadUniformFloat4(std::string_view name, const v4& value);

		void UploadUniformMat3(std::string_view name, const m3& matrix);
		void UploadUniformMat4(std::string_view name, const m4& matrix);

	private:
		uint32_t m_RenderID;
	};
}