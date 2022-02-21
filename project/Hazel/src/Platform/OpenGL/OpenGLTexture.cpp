#include "pch.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>

namespace Hazel {

	OpenGLTexture::OpenGLTexture(const string& path)
		: Texture(path)
	{
		InitOnGPU();
		stbi_image_free(m_Data);
	}

	OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height, uint32_t channels)
		: Texture(width, height, channels)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
	
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		if (m_RendererID != -1)
			glDeleteTextures(1, &m_RendererID);
	}

	OpenGLTexture& OpenGLTexture::operator=(OpenGLTexture&& other)
	{
		glDeleteTextures(1, &m_RendererID);
		m_RendererID = other.m_RendererID;
		other.m_RendererID = -1;
		m_Width = other.m_Width;
		m_Height = other.m_Height;
		m_Channels = other.m_Channels;

		return *this;
	}

	void OpenGLTexture::InitOnGPU()
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		switch (m_Channels)
		{
		case 3:
			glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_Width, m_Height); 
			glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, m_Data);
			break;
		case 4:
			glTextureStorage2D(m_RendererID, 1, GL_RGBA8, m_Width, m_Height); 
			glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, m_Data);
			break;
		default:
			HZ_ASSERT(false, "OpenGLTexture::InitOnGPU: Unsupported color channels amount!");
		}
	}

	void OpenGLTexture::SetInterpolation(TextureInterpolation interpolation) const
	{
		switch (interpolation)
		{
		case TextureInterpolation::None:
			HZ_ASSERT(false, "OpenGLTexture::SetInterpolation: \"TextureInterpolation::None\" case not expected!");
			break;
		case TextureInterpolation::Nearest:
			glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			break;
		case TextureInterpolation::Linear:
			glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
		}
	}

	void OpenGLTexture::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}


}
