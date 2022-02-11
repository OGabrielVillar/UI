#pragma once

#include "OpenGLTexture.h"

namespace Hazel {
	
	class OpenGLFramebuffer
	{
	public:
		OpenGLFramebuffer(uint32_t width, uint32_t height, uint32_t channels);
		~OpenGLFramebuffer();

		void Init();

		void Bind();
		void Unbind();
		void Unbind(vec2int resolution);

		const Texture& GetTexture() { return m_Texture; }

		void CreateDepthBuffer();

		void Resize(uint32_t width, uint32_t height);
	private:
		uint32_t m_RendererID;
		uint32_t m_DepthBufferRendererID;
		OpenGLTexture m_Texture;
	};

}
