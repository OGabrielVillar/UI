#pragma once

#include "Graphics/Renderer/VertexBuffer.h"


namespace Hazel {

	class OpenGLVertexBuffer : public VertexBuffer{
	 public:
		OpenGLVertexBuffer(float* data, unsigned int size, Reference<BufferLayout>& layout);
		virtual ~OpenGLVertexBuffer() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;
		
		virtual void ChangeBufferData(float* data, unsigned int size) override;

		virtual const BufferLayout& GetLayout() const override { return *m_Layout; }

	 private:
		uint32_t m_RenderingID;
		Reference<BufferLayout> m_Layout;
	};

}
