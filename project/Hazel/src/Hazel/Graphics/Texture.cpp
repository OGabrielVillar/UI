#include "pch.h"
#include "Texture.h"

#include "Graphics/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Hazel {

	Texture::Texture(uint32_t width, uint32_t height, uint32_t channels)
		: m_Width(width), m_Height(height), m_Channels(channels)
	{}

	Texture::Texture(const string& path)
	{
		stbi_set_flip_vertically_on_load(1);
		m_Data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channels, 0);
		HZ_ASSERT(m_Data, "Texture: Failed to load image file!")		
	}

	Ref<Texture> Texture::Create(const string& path)
	{
		switch(RendererAPI::Get())
		{
		case RendererAPI::None:   HZ_ASSERT(false, "Texture::Create: RendererAP::None not suported!") return nullptr;
		case RendererAPI::OpenGL: return CreateReference<OpenGLTexture>(path);
		}

		HZ_ASSERT(false, "Texture::Create: Unkown Renderer::API!")
		return nullptr;
	}

}
