#pragma once

#include "core.h"

#include "Window.h"

namespace Hazel {

	class Application {
	public:
		Application();
		~Application();

		void Init();

		void Run();
		bool CheckWindowsLifetime();

		/*template<typename ... Args>
		Window& CreateWindowInOtherThread(Args&& ... args)
		{
			// Defining conditioning variable(cv) for the main thread to wait for window to initialize;
			ThreadLock initialization;
			
			// Creating new window
			Window& window = m_windows.Push(std::forward<Args>(args)...);
			
			// Initializing and looping in a separated thread
			std::thread& worker = *(new std::thread([&window,&initialization](){ 
				window.Init();
				initialization.True();
				window.Run();
			}));
			worker.detach();

			// Waiting for the window initialization
			initialization.Wait();

			//window.SetThread(worker);

			return window;
		}
		Stack<Window> m_windows;*/
	private:
		Timer m_dt;
		Reference<Window> m_Window;
	};

}
