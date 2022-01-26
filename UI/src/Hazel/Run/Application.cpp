#include "pch.h"

#include "Application.h"
#include "Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Hazel 
{
	Application::~Application()
	{
		glfwTerminate();
	}

	void Application::Run()
	{
		bool running = true;
		HZ_TRACE("app checking...");
		while(running) {

			// Check Windows Lifetime
			for (Window& window : m_windows){
				if (!window.IsAlive())
				{
					m_windows.DeleteCurrent();
				HZ_TRACE("Window Deleted!");
				}
			}

			if (m_windows.IsEmpty()) {
				HZ_INFO("ALL WINDOWS WERE CLOSED...\n  QUITTING PROGRAM...");
			} else {
				HZ_TRACE(" ... ");
			}

			std::this_thread::sleep_for(2.5_seconds);

		}

	}

}
