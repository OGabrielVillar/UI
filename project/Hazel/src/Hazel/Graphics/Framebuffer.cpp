#include "pch.h"
#include "Framebuffer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

#include "RendererAPI.h"

namespace Hazel {

	Ref<Framebuffer> Framebuffer::Create(uint32_t width, uint32_t height, uint32_t channels)
	{
		switch(RendererAPI::Get())
		{
		case RendererAPI::None:   HZ_ASSERT(false, "Framebuffer::Create: RendererAP::None not suported!") return nullptr;
		case RendererAPI::OpenGL: return CreateReference<OpenGLFramebuffer>(width, height, channels);
		}

		HZ_ASSERT(false, "Framebuffer::Create: Unkown Renderer::API!")
		return nullptr;
	}

}
