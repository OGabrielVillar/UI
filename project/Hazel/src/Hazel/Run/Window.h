#pragma once
#include <GLFW/glfw3.h>

#include "Core/Geometry/Rect.h"
#include "Graphics/RenderingContext.h"
#include "Input/Event.h"
#include "Structure/Canvas.h"

namespace Hazel {

	using EventCallbackFn = std::function<bool(const Event&)>;

	enum class WindowFlag : uint8_t {
		Maximazed		= BIT(0),
		Iconified		= BIT(1),
		Focused			= BIT(2),
		Hidden			= BIT(3),
		Decorated		= BIT(4),
		Transparent		= BIT(5),
	};

	class Window {
	 public:
		using Flag = WindowFlag;
		using Flags = Flags<WindowFlag, Flag::Focused>;

	 public:
		Window(const std::string& name, Flags flags = Flag::Focused);
		~Window();

	 public:
		void Init(); 
		void InitCallbacks();
		void Shutdown();

	 public:
		void Run();
		void Minimize();
		void Resume();
		int IsAlive();
		void Close();

		void Maximize();
		void Restore();
		void SetPosition(int x, int y);
		void SetSize(int width, int height);
		void CenterWindow();
		void SetOnEventCallback(const EventCallbackFn& callback) { m_OnEventCallbackFn = callback; }

		void SetName(std::string&& name) { m_Name = name; }
		void SetColor(const vec4& color) { m_Context->SetColor(color); }
		void SetTitle(const std::string& title);
		Ref<Canvas> GetCanvas() { return Ref<Canvas>(m_Canvas); }
		const vec2int& GetResolution() const { return m_Canvas->GetSize(); }
		const vec2int& GetPosition() const { return m_TopLeft; }

		inline bool IsMaximized() const { return m_Flags.Contains(Flag::Maximazed); }
		inline bool IsIconified() const { return m_Flags.Contains(Flag::Iconified); }
		inline bool IsFocused() const { return m_Flags.Contains(Flag::Focused); }

	 private:
		GLFWwindow* m_Window = nullptr;
		Reference<RenderingContext> m_Context = nullptr;
		std::string m_Name;
		Flags m_Flags;
		vec2int m_TopLeft;
		vec2int m_MonitorResolution;

		Ref<Canvas> m_Canvas = CreateReference<Canvas>(intRect::WH(720, 720));
		EventCallbackFn m_OnEventCallbackFn;
	};

}
