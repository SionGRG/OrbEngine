#include "OrbPCH.h"
#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace ORB {

	static GLenum ShaderTypeFromString(std::string_view type)
	{
		if (type == "vertex") 
			return GL_VERTEX_SHADER;
		else if (type == "fragment" || type == "pixel") 
			return GL_FRAGMENT_SHADER;

		ORBE_CORE_ASSERT(false, "Unknown shader type!'");
		return 0;
	}
	
	OpenGLShader::OpenGLShader(std::string_view filepath)
	{
		std::string source = ReadFile(filepath);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);

		// Extract name from filepath
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string_view::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string_view::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(std::string_view name, std::string_view vertexSrc, std::string_view fragmentSrc)
		: m_Name(name)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
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

	void OpenGLShader::SetInt(std::string_view name, int value)
	{
		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetFloat3(std::string_view name, const v3& value)
	{
		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(std::string_view name, const v4& value)
	{
		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetMat4(std::string_view name, const m4& value)
	{
		UploadUniformMat4(name, value);
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

	std::string OpenGLShader::ReadFile(std::string_view filepath)
	{
		std::string result;
		std::ifstream in(filepath.data(), std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
				in.close();
			}
			else
			{
				ORBE_CORE_ASSERT("Could no read from file '{0}'", filepath);
			}
		}
		else
		{
			ORBE_CORE_ERROR("Could not open file '{0}'", filepath);
		}
		
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(std::string_view source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);

		size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);//End of shader type declaration line
			ORBE_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
			std::string_view type = source.substr(begin, eol - begin);
			ORBE_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified!");

			size_t nextLinePos = source.find_first_not_of("|r|n", eol);//Start of shader code after shader type declaration line
			pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line
			shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		// Get a program object.
		GLuint program = glCreateProgram();
		ORBE_CORE_ASSERT(shaderSources.size() <= 2, "We only support a maximum amount of 2 shaders!");
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;

		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			std::string_view source = kv.second;
			
			// Create an empty shader handle of specified type
			GLuint shader = glCreateShader(type);

			// Send the 'specified type' shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* sourceCStr = source.data();
			glShaderSource(shader, 1, &sourceCStr, 0);

			// Compile the 'specified type' shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				ORBE_CORE_ERROR("{0}", infoLog.data());
				ORBE_CORE_ASSERT(false, "Shader compilation failure!");

				break;
			}

			// The shader has successfully compiled.
			// Now time to link it together into a program.
			glAttachShader(program, shader);

			glShaderIDs[glShaderIDIndex++] = shader;
		}

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);

			// Don't leak shaders either.
			for(auto id : glShaderIDs)
				glDeleteShader(id);

			ORBE_CORE_ERROR("{0}", infoLog.data());
			ORBE_CORE_ASSERT(false, "Shader link failure!");

			return;
		}

		// Always detach shaders after a successful link
		for (auto id : glShaderIDs)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}

		// Assign the program object to the RenderID.
		m_RenderID = program;
	}
}