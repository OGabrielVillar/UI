#pragma once

#include "Graphics/Texture.h"

namespace Hazel {

	class OpenGLTexture : public Texture {
	public:
		OpenGLTexture(const string& path);
		OpenGLTexture(uint32_t width, uint32_t height, uint32_t channels);
		virtual ~OpenGLTexture();

		OpenGLTexture& operator=(OpenGLTexture&& other);

		virtual void InitOnGPU() override;
		
		virtual void SetInterpolation(TextureInterpolation interpolation) const override;
		virtual void Bind(uint32_t slot = 0) const override;

		uint32_t GetId() { return m_RendererID; };


	private:
		uint32_t m_RendererID;
	};

}
