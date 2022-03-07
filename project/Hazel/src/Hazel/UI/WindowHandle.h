#pragma once

#include "Run/Window.h"

namespace Hazel {

	struct WindowHandle {
	public:
		WindowHandle(Window& window)
			: m_Window(window)
		{}
		WindowHandle& operator=(const WindowHandle& other) { return *this; }

		void OnDrag(int x, int y);
		void OnLeftPress(int x, int y);
		void OnLeftRelease(int x, int y);

	private:
		vec2int m_StartCursorPosition = { 0,0 };
		vec2int m_StartWindowPosition = { 0,0 };
		vec2int m_Difference = { 0,0 };
		bool m_IsDragging = false;
		Window& m_Window;
	};
	
}
