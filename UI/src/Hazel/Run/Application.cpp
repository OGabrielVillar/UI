#include "pch.h"

#include "Application.h"
#include "Log.h"

namespace Hazel 
{

	void Application::Run()
	{
		bool running = true;
		while(running) {
			HZ_INFO("app checking...");
			int many_nulls = 0;
			for(Reference<Window>& window : m_windows) {

				if (window){
					if (!window->IsAlive()) {
						HZ_INFO("ENDING WINDOW.");
						window->GetThread().join();
						window.reset();
						many_nulls++;
					}

				} else {

					many_nulls++;

				}
			}

			if (many_nulls == m_windows.size())
				running = false;

			std::this_thread::sleep_for(5.0_seconds);

		}
		
		HZ_INFO("QUITTING PROGRAM...");

		std::this_thread::sleep_for(5.0_seconds);

	}

}
