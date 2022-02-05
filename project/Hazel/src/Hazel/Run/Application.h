#pragma once

#include "Window.h"

#include "Graphics/Renderer/Shader.h"
#include "Graphics/Renderer/VertexBuffer.h"
#include "Graphics/Renderer/IndexBuffer.h"
#include "Graphics/Renderer/VertexArray.h"
#include "Scene/Camera.h"

namespace Hazel {

	class Application {
	public:
		Application(const std::string& name, Window::Flags flags = Window::Flags());
		virtual ~Application();

		virtual void OnInit() {}
		virtual void OnShutdown() {}
		virtual void OnUpdate() {}
		virtual bool OnEvent(const Event&) { return false; }

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

	 protected:
		Timer m_dt_timer;
		float m_dt;
		Reference<Window> m_Window;
	};

}
