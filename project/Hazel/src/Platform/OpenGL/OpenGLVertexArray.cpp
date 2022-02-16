#include "pch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Hazel {

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	static GLenum ToOpenGLBaseType(BufferLayoutDataType type) {
		switch (type)
		{
			case Hazel::BufferLayoutDataType::Bool:		  return GL_BOOL;
			case Hazel::BufferLayoutDataType::Float:	  return GL_FLOAT;
			case Hazel::BufferLayoutDataType::Float2:	  return GL_FLOAT;
			case Hazel::BufferLayoutDataType::Float3:	  return GL_FLOAT;
			case Hazel::BufferLayoutDataType::Float4:	  return GL_FLOAT;
			case Hazel::BufferLayoutDataType::Int:		  return GL_INT;
			case Hazel::BufferLayoutDataType::Int2:		  return GL_INT;
			case Hazel::BufferLayoutDataType::Int3:		  return GL_INT;
			case Hazel::BufferLayoutDataType::Int4:		  return GL_INT;
			case Hazel::BufferLayoutDataType::Mat3:		  return GL_FLOAT;
			case Hazel::BufferLayoutDataType::Mat4:		  return GL_FLOAT;
		}
		HZ_ASSERT(false,"[Hazel::ToOpenGLBaseType] Unsupported \"BufferLayoutDataType\" case!");
		return 0;
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vectorBuffer)
	{
		glBindVertexArray(m_RendererID);
		vectorBuffer->Bind();
		
		HZ_ASSERT(vectorBuffer->GetLayout().GetElements().size(), "OpenGLVertexArray::AddVertexBuffer Vector Buffer input has no layout!")

		uint32_t index = 0;
		auto& layout = vectorBuffer->GetLayout();
		for (auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, 
				element.Count, 
				ToOpenGLBaseType(element.Type), 
				element.Normalized ? GL_FALSE : GL_TRUE, 
				layout.GetStride(), 
				(const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vectorBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}
