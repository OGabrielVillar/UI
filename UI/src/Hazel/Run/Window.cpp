#include "pch.h"

#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Log.h"

namespace Hazel {

	Window::Window()
	{
		//Init();
	}

	Window::Window(std::string&& name)
		: m_name(name)
	{
		//Init();
	}

	Window::~Window()
	{
		Shutdown();
	}

	void Window::Init()
	{
		HZ_WARN("Creating Window...");

		/* Initialize the library */
		if (!glfwInit())
			return;

		// Remove TitleBar
		//glfwWindowHint(GLFW_DECORATED, false);

		//Transparent Window?
		//glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);

		/* Create a windowed mode window and its OpenGL context */
		m_window = glfwCreateWindow(m_rect.width, m_rect.height, m_name.c_str(), NULL, NULL);
		
		/* Make the window's context current */
		glfwMakeContextCurrent(m_window);
		
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_ASSERT(!status,"Failed to load Grad!");

		int monitor_width, monitor_height;
		glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), nullptr, nullptr, &monitor_width, &monitor_height);

		// Move Window
		glfwSetWindowPos(m_window,
			(monitor_width / 2) - (m_rect.width / 2),
			(monitor_height / 2) - (m_rect.height / 2));

		if (!m_window)
		{
			glfwTerminate();
			return;
		}

	}

	void Window::SetSize(int width, int height)
	{
		glfwSetWindowSize(m_window, width, height);
	}

	void Window::Run()
	{
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(m_window))
		{

			glfwPollEvents();

			glClearColor(m_color.r,m_color.g,m_color.b, 1.0f);

			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(m_window);

		}

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

	void Window::Shutdown()
	{
		glfwTerminate();
	}

}
