#include "pch.h"
#include "VertexBuffer.h"

#include "../Platform/OpenGL/OpenGLVertexBuffer.h"

#include "Renderer.h"

#include "Run/Log.h"

namespace Hazel {

	VertexBuffer* VertexBuffer::Create(float* data, uint32_t size)
	{
		switch(Renderer::API())
		{
		case RendererAPI::None:   HZ_ASSERT(false, "VertexBuffer::Create: RendererAP::None not suported!") return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexBuffer(data,size);
		}

		HZ_ASSERT(false, "VertexBuffer::Create: Unkown Renderer::API!")
		return nullptr;
	}

}
