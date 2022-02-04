#pragma once

#include "core.h"

#include "Window.h"

#include "Graphics/Renderer/Shader.h"
#include "Graphics/Renderer/VertexBuffer.h"
#include "Graphics/Renderer/IndexBuffer.h"
#include "Graphics/Renderer/VertexArray.h"
#include "Scene/Camera.h"

namespace Hazel {

	class Application {
	public:
		Application();
		virtual ~Application();

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

	 private:// Shit
		void InitShit();
		void TestShit();
		Reference<Shader> m_Shader;
		Reference<VertexArray> m_VertexArray;

		Reference<Shader> m_SquareShader;
		Reference<VertexArray> m_SquareVA;

		Camera m_Camera = Rect(-1.777777777f, 1.777777777f, 1.f, -1.f);

	 protected:
		Timer m_dt_timer;
		float m_dt;
		Reference<Window> m_Window;
		Rect m_Rect = Rect::LTRB(50.f,50.f,370.f,170.f);
		vec4 m_RectColor = { 0.9f, 0.75f, 0.8f, 1.f };
	};

}
