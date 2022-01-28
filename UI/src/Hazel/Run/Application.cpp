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
			
			Timer timer;
			// Check Windows Lifetime
			for (auto window : m_windows){
				if (!window->IsAlive())
				{
					window.Delete();
				HZ_TRACE("Window Deleted!");
				}
			}

			if (m_windows.IsEmpty()) {
				HZ_INFO("ALL WINDOWS WERE CLOSED...\n  QUITTING PROGRAM...");
				std::cin.get();
				running = false;
			} else {
				std::cout << "... " << Time::milliseconds(timer.update()) << std::endl;
				std::this_thread::sleep_for(2.5_seconds);
			}

		}

	}

}
