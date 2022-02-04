#include "pch.h"
#include "VertexArray.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

#include "RendererAPI.h"

#include "Run/Log.h"

namespace Hazel {

	Reference<VertexArray> VertexArray::Create()
	{
			switch(RendererAPI::Get())
			{
			case RendererAPI::None:   HZ_ASSERT(false, "VertexArray::Create: RendererAP::None not suported!") return nullptr;
			case RendererAPI::OpenGL: return CreateReference<OpenGLVertexArray>();
			}

			HZ_ASSERT(false, "VertexArray::Create: Unkown Renderer::API!")
			return nullptr;
	}

}
