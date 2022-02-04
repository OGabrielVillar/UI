#include "pch.h"

#include "Window.h"

#include <GLFW/glfw3.h>

#include "Log.h"
#include "Platform/OpenGL/OpenGLRenderingContext.h"

#include "Graphics/Renderer/Renderer.h"

namespace Hazel {

	Window::Window()
	{}

	Window::Window(std::string&& name)
		: m_name(name)
	{}

	Window::~Window()
	{
		HZ_WIN_TRACE(" ... Destructed!");
		glfwTerminate();
	}

	void Window::Init()
	{
		HZ_WIN_TRACE("Initializing ... ");

		/* Initialize the library */
		if (!glfwInit())
			return;

		// Remove TitleBar
		glfwWindowHint(GLFW_DECORATED, false);

		//Transparent Window?
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);

		/* Create a windowed mode window and its OpenGL context */
		m_window = glfwCreateWindow(m_rect.width(), m_rect.height(), m_name.c_str(), NULL, NULL);

		m_context = CreateReference<OpenGLRenderingContext>(m_window);
		m_context->Init();
		
		// Move window
		int monitor_width, monitor_height;
		glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), nullptr, nullptr, &monitor_width, &monitor_height);

		glfwSetWindowPos(m_window,
			(monitor_width / 2) - (m_rect.width() / 2),
			(monitor_height / 2) - (m_rect.height() / 2));

		Renderer::SetWindowSize(m_rect.width(), m_rect.height());

		if (!m_window)
		{
			glfwTerminate();
			return;
		}

	}

	void Window::Run()
	{
		//HZ_WIN_TRACE("Start running ... ");
		glfwPollEvents();
		m_context->SwapBuffers();
	}
	
	void Window::SetSize(int width, int height)
	{
		glfwSetWindowSize(m_window, width, height);
	}

	void Window::Minimize()
	{
		glfwIconifyWindow(m_window);
	}

	void Window::Resume()
	{
		glfwRestoreWindow(m_window);
	}

	int Window::IsAlive()
	{
		return !glfwWindowShouldClose(m_window);
	}

	void Window::Close()
	{
		glfwSetWindowShouldClose(m_window,true);
	}

}
