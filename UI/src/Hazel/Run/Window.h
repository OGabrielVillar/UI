#pragma once
#include <string>

#include <GLFW/glfw3.h>

#include "core.h"

#include "../Graphics/Renderer/RenderingContext.h"

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
		void SetColor(const vec4& color) { m_context->SetColor(color); }
	private:
		GLFWwindow* m_window = nullptr;
		Reference<RenderingContext> m_context = nullptr;
		std::string m_name;
		std::string m_thread_id;
		//intRect m_rect = { 0,0,174*8,100*8 };
		intRect m_rect = { 0,0,1280,720 };
		//intRect m_rect = { 0,0,1920,1080 };

		ThreadLock m_inert;
	};

}
