#pragma once

#include "Graphics/VertexArray.h"

namespace Hazel {

	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vectorBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
		
		virtual const std::vector<Reference<VertexBuffer>> GetVertexBuffers() const override
			{ return m_VertexBuffers; }
		virtual const Reference<IndexBuffer> GetIndexBuffer() const override
			{ return m_IndexBuffer; }

	private:
		uint32_t m_RendererID;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

	};

}
