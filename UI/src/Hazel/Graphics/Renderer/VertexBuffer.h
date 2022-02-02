#pragma once

#include "core.h"

namespace Hazel {

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {}
	
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	
		static VertexBuffer* Create(float* data, uint32_t size);
	};

}
