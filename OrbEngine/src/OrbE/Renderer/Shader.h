#pragma once

#include <string>
#include "OrbE/Maths/BasicMath.h"
namespace ORB {

	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformFloat4(std::string_view name, const v4& values);
		void UploadUniformMat4(std::string_view name, const m4& matrix);
	private:

		uint32_t m_RenderID;
	};
}