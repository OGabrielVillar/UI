#pragma once
#include <string>

#include <GLFW/glfw3.h>

#include "Core/Geometry/Rect.h"

#include "Graphics/Renderer/RenderingContext.h"
#include "Input/Event.h"

namespace Hazel {

 // Flags
	enum class WindowFlag : uint8_t {
		Maximazed		= BIT(0),
		Iconified		= BIT(1),
		Focused			= BIT(2),
		Hidden			= BIT(3),
		Decorated		= BIT(4),
		Transparent		= BIT(5),
	};

 // --- WINDOW CLASS ---

	class Window {
	 public:
		using Flag = WindowFlag;
		using Flags = Flags<WindowFlag, Flag::Focused>;
	 public:
		Window(const std::string& name, Flags flags = Flag::Focused);
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
		void SetOnEventCallback(const EventCallbackFn& callback) { m_OnEventCallbackFn = callback; }

		void SetName(std::string&& name) { m_Name = name; }
		void SetColor(const vec4& color) { m_Context->SetColor(color); }
	 private:
		GLFWwindow* m_Window = nullptr;
		Reference<RenderingContext> m_Context = nullptr;
		std::string m_Name;
		Flags m_Flags;
		intRect m_Rect = intRect::LTRB(0, 0, 1280, 720);
		EventCallbackFn m_OnEventCallbackFn;
		//struct WindowData {
		//	Window window; 
		//};
		//WindowData m_Data;
	};

}
