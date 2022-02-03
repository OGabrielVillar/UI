#include "pch.h"
#include "IndexBuffer.h"

#include "../Platform/OpenGL/OpenGLIndexBuffer.h"

#include "Renderer.h"

#include "Run/Log.h"

namespace Hazel {
	
	Reference<IndexBuffer> IndexBuffer::Create(uint32_t* data, uint32_t size)
	{
		switch(Renderer::API())
		{
		case RendererAPI::None:   HZ_ASSERT(false, "IndexBuffer::Create: RendererAP::None not suported!") return nullptr;
		case RendererAPI::OpenGL: return CreateReference<OpenGLIndexBuffer>(data,size);
		}

		HZ_ASSERT(false, "IndexBuffer::Create: Unkown Renderer::API!")
		return nullptr;
	}

}
