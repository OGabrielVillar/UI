#pragma once

namespace Hazel {
	
	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		virtual uint32_t GetCount() const = 0;

		static Reference<IndexBuffer> Create(uint32_t* data, uint32_t count);
	};

}
