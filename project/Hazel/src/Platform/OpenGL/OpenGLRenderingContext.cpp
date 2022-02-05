#include "pch.h"
#include "OpenGLRenderingContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Graphics/Renderer/BufferLayout.h"

namespace Hazel {

	OpenGLRenderingContext::OpenGLRenderingContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)
	{
		HZ_ASSERT(windowHandle,"OpenGLRenderingContext: Window handle is null!");
	}

	OpenGLRenderingContext::~OpenGLRenderingContext()
	{}

	void OpenGLRenderingContext::Init()
	{
		// Make the window's context current
		glfwMakeContextCurrent(m_windowHandle);

		// Lock the maximum refresh rate of the context to the display's maximum hz, sync.
		//     0 = off, 1 = on.
		glfwSwapInterval(1);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_ASSERT(status,"OpenGLRenderingContext: Failed to load Glad!");
		
		HZ_WIN_TRACE("Vendor: {}", glGetString(GL_VENDOR));
		HZ_WIN_TRACE("Renderer: {}", glGetString(GL_RENDERER));
		HZ_WIN_TRACE("Version: {}", glGetString(GL_VERSION));
	}

	void OpenGLRenderingContext::SwapBuffers() 
	{
		glfwSwapBuffers(m_windowHandle);
	}

}
