#include "OrbPCH.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace ORB {

	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			ORBE_CORE_ERROR("{0}", infoLog.data());
			ORBE_CORE_ASSERT(false, "Vertex shader compilation failure!");

			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			ORBE_CORE_ERROR("{0}", infoLog.data());
			ORBE_CORE_ASSERT(false, "Fragment shader compilation failure!");

			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RenderID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_RenderID, vertexShader);
		glAttachShader(m_RenderID, fragmentShader);

		// Link our program
		glLinkProgram(m_RenderID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_RenderID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RenderID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RenderID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_RenderID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			ORBE_CORE_ERROR("{0}", infoLog.data());
			ORBE_CORE_ASSERT(false, "Shader link failure!");

			return;
		}

	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RenderID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RenderID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(std::string_view name, int value)
	{
		GLint location = glGetUniformLocation(m_RenderID, name.data());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(std::string_view name, float value)
	{
		GLint location = glGetUniformLocation(m_RenderID, name.data());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(std::string_view name, const v2& value)
	{
		GLint location = glGetUniformLocation(m_RenderID, name.data());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(std::string_view name, const v3& value)
	{
		GLint location = glGetUniformLocation(m_RenderID, name.data());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(std::string_view name, const v4& value)
	{
		GLint location = glGetUniformLocation(m_RenderID, name.data());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(std::string_view name, const m3& matrix)
	{
		GLint location = glGetUniformLocation(m_RenderID, name.data());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(std::string_view name, const m4& matrix)
	{
		GLint location = glGetUniformLocation(m_RenderID, name.data());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}