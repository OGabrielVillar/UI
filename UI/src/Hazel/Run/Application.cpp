#include "pch.h"

#include "Application.h"
#include "Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Hazel 
{
	Application::Application()
	{
		Init();
	}
	Application::~Application()
	{
		glfwTerminate();
	}

	void Application::Init()
	{
		HZ_APP_TRACE("Initializing ... ");

		m_Window = CreateReference<Window>("Hazel");
		m_Window->Init();
	}

	void Application::Run()
	{
		bool running = true;
		HZ_APP_TRACE("Start running ... ");

		m_dt.update();
		HZ_WIN_TRACE("Start running ... ");
		/* Loop until the user closes the window */
		while (m_Window->IsAlive()) {
			m_Window->Run();
		}
		HZ_WIN_TRACE(" ... Stop running!");
		std::cin.get();
	}

}
