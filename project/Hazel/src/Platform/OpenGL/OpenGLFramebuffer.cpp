#include "pch.h"
#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace Hazel {

	OpenGLFramebuffer::OpenGLFramebuffer(uint32_t width, uint32_t height, uint32_t channels = 4)
		: m_Texture(width, height, channels)
	{
		Init();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteRenderbuffers(1, &m_DepthBufferRendererID);
		glDeleteFramebuffers(1, &m_RendererID);
	}

	void OpenGLFramebuffer::Init()
	{
		// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
		glGenFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		// Texture
		m_Texture.Bind();

		// The depth buffer
		CreateDepthBuffer();

		// Set "m_Texture" as our colour attachement #0
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_Texture.GetId(), 0);

		// Set the list of draw buffers.
		GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
		glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

		// Always check that our framebuffer is ok
		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			HZ_ASSERT(false, "OpenGLFramebuffer::Init: Framebuffer initialization failed!")
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Texture.GetWidth(), m_Texture.GetHeight());
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Unbind(vec2int resolution)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, resolution.x, resolution.y);
	}

	void OpenGLFramebuffer::CreateDepthBuffer()
	{
		glGenRenderbuffers(1, &m_DepthBufferRendererID);
		glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBufferRendererID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_Texture.GetWidth(), m_Texture.GetHeight());
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBufferRendererID);
	}

	void OpenGLFramebuffer::Resize(const vec2int& vector)
	{
		Resize(vector.x, vector.y);
	}

	void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		m_Texture = OpenGLTexture(width, height, m_Texture.GetChannels());
		m_Texture.Bind();

		glDeleteRenderbuffers(1, &m_DepthBufferRendererID);
		CreateDepthBuffer();

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_Texture.GetId(), 0);

		GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
		glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

		// Always check that our framebuffer is ok
		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			HZ_ASSERT(false, "OpenGLFramebuffer::Init: Framebuffer initialization failed!")
		}
	}

}
