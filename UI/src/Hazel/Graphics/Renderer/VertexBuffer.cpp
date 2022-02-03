#include "pch.h"
#include "VertexBuffer.h"

#include "../Platform/OpenGL/OpenGLVertexBuffer.h"

#include "Renderer.h"

#include "Run/Log.h"

namespace Hazel {

	Reference<VertexBuffer> VertexBuffer::Create(float* data, uint32_t size, Reference<BufferLayout>& layout)
	{
		switch(Renderer::API())
		{
		case RendererAPI::None:   HZ_ASSERT(false, "VertexBuffer::Create: RendererAP::None not suported!") return nullptr;
		case RendererAPI::OpenGL: return CreateReference<OpenGLVertexBuffer>(data, size, layout);
		}

		HZ_ASSERT(false, "VertexBuffer::Create: Unkown Renderer::API!")
		return nullptr;
	}

}
