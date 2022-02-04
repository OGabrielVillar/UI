#pragma once

#include "core.h"
#include "BufferLayout.h"

namespace Hazel {

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {}
	
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual const BufferLayout& GetLayout() const = 0;
		virtual void ChangeBufferData(float* data, unsigned int size) = 0;
	
		static Reference<VertexBuffer> Create(float* data, uint32_t size, Reference<BufferLayout>& layout);
	};

}
