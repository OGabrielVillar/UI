#pragma once

#include "stb_image.h"

namespace Hazel {

	enum class TextureInterpolation : uint8_t {
		None,
		Nearest,
		Linear,
	};

	enum class TextureBlend : uint8_t {
		None,
		Nearest,
		Linear,
	};

	class Texture {
	public:
		Texture(uint32_t width, uint32_t height, uint32_t channels);
		Texture(const string& path);
		virtual ~Texture() = default;

		virtual void InitOnGPU() {}

		virtual void SetInterpolation(TextureInterpolation interpolation) const = 0;
		virtual void Bind(uint32_t slot = 0) const = 0;

		int GetWidth() { return m_Width; }
		int GetHeight() { return m_Height; }
		int GetChannels() { return m_Channels; }

		static Ref<Texture> Create(const string& path);
	protected:
		int m_Width, m_Height, m_Channels;
		stbi_uc* m_Data;
		//TextureInterpolation m_MagInterpolation, m_MinInterpolation;
	};

}
