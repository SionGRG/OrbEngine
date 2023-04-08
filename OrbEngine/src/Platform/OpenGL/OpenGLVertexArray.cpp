#include "OrbPCH.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace ORB {
	
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:     return GL_FLOAT;
			case ShaderDataType::Float2:    return GL_FLOAT;
			case ShaderDataType::Float3:    return GL_FLOAT;
			case ShaderDataType::Float4:    return GL_FLOAT;
			case ShaderDataType::Mat3:      return GL_FLOAT;
			case ShaderDataType::Mat4:      return GL_FLOAT;
			case ShaderDataType::Int:       return GL_INT;
			case ShaderDataType::Int2:      return GL_INT;
			case ShaderDataType::Int3:      return GL_INT;
			case ShaderDataType::Int4:      return GL_INT;
			case ShaderDataType::Bool:      return GL_BOOL;
		}

		ORBE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RenderID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RenderID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RenderID);
	}
	
	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
	
	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		ORBE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		// Bind the Render ID for the vertex array and vertex buffer
		glBindVertexArray(m_RenderID);
		vertexBuffer->Bind();

		uint32_t vertexBufferIndex = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (auto& element : layout)
		{
			glEnableVertexAttribArray(vertexBufferIndex);
			glVertexAttribPointer(vertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(intptr_t)element.Offset);
			vertexBufferIndex++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		// Bind the Render ID for the vertex array and index buffer
		glBindVertexArray(m_RenderID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}