#include "pch.h"
#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

namespace Hazel 
{
	
	// ---- VERTEX BUFFER ----

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* data, uint32_t size)
	{
		glCreateBuffers(1, &m_RenderingID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderingID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RenderingID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderingID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}
