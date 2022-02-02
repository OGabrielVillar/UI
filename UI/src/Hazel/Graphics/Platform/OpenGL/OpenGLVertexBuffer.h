#pragma once

#include "../../Renderer/VertexBuffer.h"
#include "../../Renderer/BufferLayout.h"

namespace Hazel {

	class OpenGLVertexBuffer : public VertexBuffer{
	 public:
		OpenGLVertexBuffer(float* data, unsigned int size);
		virtual ~OpenGLVertexBuffer() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;
	 private:
		uint32_t m_RenderingID;
		//BufferLayout*
	};

}
