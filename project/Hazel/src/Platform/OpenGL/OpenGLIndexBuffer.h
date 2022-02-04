#pragma once
#include "Graphics/Renderer/IndexBuffer.h"

namespace Hazel {
	
	class OpenGLIndexBuffer : public IndexBuffer {
	 public:
		OpenGLIndexBuffer(uint32_t* data, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		
		virtual uint32_t GetCount() const override;
	 private:
		uint32_t m_RenderingID;
		uint32_t m_Count;
	};

}
