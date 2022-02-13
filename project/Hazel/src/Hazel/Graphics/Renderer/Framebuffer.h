#pragma once

#include "Graphics/Texture.h"

namespace Hazel {
	
	class Framebuffer
	{
	public:
		virtual void Init() = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Unbind(vec2int resolution) = 0;
		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual const Texture& GetTexture() const = 0;

		static Ref<Framebuffer> Create(uint32_t width, uint32_t height, uint32_t channels);
	};

}
