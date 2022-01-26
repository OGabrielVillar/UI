#pragma once

#include "core.h"

#include "Window.h"

namespace Hazel {

	class Application {
	public:
		Application() = default;
		~Application();
		void Init();
		void Shutdown();

		void Run();

		template<typename ... Args>
		Window& CreateWindow(Args&& ... args)
		{

			Window& window = m_windows.Push(std::forward<Args>(args)...);

			Reference<std::thread> worker = CreateReference<std::thread>([&window = window](){ 
				window.Init();
				window.Run();
			});

			worker->detach();

			window.SetThread(worker);

			return window;

		}
	private:
		tryStack<Window> m_windows;
	};

}
