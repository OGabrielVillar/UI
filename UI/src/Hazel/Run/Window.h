#pragma once
#include <string>

#include <GLFW/glfw3.h>

#include "core.h"

namespace Hazel {

	class Window {
	public:
		Window();
		Window(std::string&& name);
		~Window();
	public:
		void Init();
		void Shutdown();
	public:
		void Run();
		void Minimize();
		void Resume();
		//void Maximize();
		int IsAlive();
		void Close();

		void SetPosition(int width, int height);
		void SetSize(int width, int height);

		void SetName(std::string&& name) { m_name = name; }
		void SetColor(const vec4& color) { m_color = color; }
		void SetThread(Reference<std::thread> thread) { m_thread = thread; }
		std::thread& GetThread() { return *m_thread; }
	private:
		GLFWwindow* m_window;
		std::string m_name;
		intRect m_rect = { 0,0,174*8,100*8 };
		Reference<std::thread> m_thread = nullptr;

		vec4 m_color = {.99f,.8f,.85f, 1.0f};
	};

}
