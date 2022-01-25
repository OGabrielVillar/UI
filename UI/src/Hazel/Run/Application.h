#pragma once

#include "core.h"

#include "Window.h"

namespace Hazel {

	class Application {
	public:
		Application() = default;
		~Application() = default;
		void Init();
		void Shutdown();

		void Run();

		template<typename ... Args>
		Window& CreateWindow(Args&& ... args)
		{
			Reference<Window> window = CreateReference<Window>(std::forward<Args>(args)...);
			m_windows.push_back(window);
			Reference<std::thread> worker = CreateReference<std::thread>([&window = *window](){ 
				window.Init();
				window.Run();
			});
			window->SetThread(worker);
			return *window.get();
		}
	private:
		std::vector<Reference<Window>> m_windows;
	};

}
