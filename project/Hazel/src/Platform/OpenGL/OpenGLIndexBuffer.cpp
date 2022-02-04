#include "pch.h"
#include "OpenGLIndexBuffer.h"

#include <glad/glad.h>

namespace Hazel 
{
	// ---- INDEX BUFFER ----

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* data, uint32_t count)
		: m_Count(count)
	{
		glCreateBuffers(1, &m_RenderingID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderingID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RenderingID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderingID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	uint32_t OpenGLIndexBuffer::GetCount() const
	{
		return m_Count;
	}

}
