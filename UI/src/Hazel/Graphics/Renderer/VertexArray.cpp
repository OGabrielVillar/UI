#include "pch.h"
#include "VertexArray.h"

#include "../Platform/OpenGL/OpenGLVertexArray.h"

#include "Renderer.h"

#include "Run/Log.h"

namespace Hazel {

	Reference<VertexArray> VertexArray::Create()
	{
			switch(Renderer::API())
			{
			case RendererAPI::None:   HZ_ASSERT(false, "VertexArray::Create: RendererAP::None not suported!") return nullptr;
			case RendererAPI::OpenGL: return CreateReference<OpenGLVertexArray>();
			}

			HZ_ASSERT(false, "VertexArray::Create: Unkown Renderer::API!")
			return nullptr;
	}

}
