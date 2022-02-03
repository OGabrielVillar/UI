#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Hazel  
{
	
	class VertexArray {
	public:
		virtual ~VertexArray() {}

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Reference<VertexBuffer>> GetVertexBuffers() const = 0;
		virtual const Reference<IndexBuffer> GetIndexBuffer() const = 0;

		static Reference<VertexArray> Create();
	};

}
