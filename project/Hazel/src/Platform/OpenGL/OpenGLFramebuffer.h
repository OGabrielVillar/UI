#pragma once

#include "OpenGLTexture.h"
#include "Graphics/Renderer/Framebuffer.h"

namespace Hazel {
	
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(uint32_t width, uint32_t height, uint32_t channels);
		~OpenGLFramebuffer();

		virtual void Init() override;

		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void Unbind(vec2int resolution) override;
		virtual const Texture& GetTexture() const override { return m_Texture; }

		void CreateDepthBuffer();

		void Resize(uint32_t width, uint32_t height);
	private:
		uint32_t m_RendererID;
		uint32_t m_DepthBufferRendererID;
		OpenGLTexture m_Texture;
	};

}
