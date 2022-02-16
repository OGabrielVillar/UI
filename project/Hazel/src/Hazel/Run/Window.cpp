#include "pch.h"

#include "Window.h"

#include <GLFW/glfw3.h>

#include "Platform/OpenGL/OpenGLRenderingContext.h"

#include "Graphics/Renderer/Renderer.h"
#include "Device/Keyboard/Keyboard.h"
#include "Device/Mouse/Mouse.h"
#include "Input/Cursor.h"

namespace Hazel {

	Window::Window(const std::string& name, Flags flags)
		: m_Name(name), m_Flags((Flags)flags)
	{}

	Window::~Window()
	{
		HZ_WIN_TRACE(" ... Destructed!");
		glfwTerminate();
	}

	void Window::Init()
	{
		HZ_WIN_TRACE("Initializing ... ");

		/* Initialize the library */
		if (!glfwInit())
			return;

		// Flag Decorated
		if (m_Flags.NotContains(Window::Flag::Decorated))
			glfwWindowHint(GLFW_DECORATED, false);

		// Flag Transparent
		if (m_Flags.Contains(Window::Flag::Transparent))
			glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);
		
		// Flag Maximazed
		if (m_Flags.Contains(Window::Flag::Maximazed))
			glfwWindowHint(GLFW_MAXIMIZED, true);
		
		// Flag Focused
		if (m_Flags.NotContains(Window::Flag::Focused))
			glfwWindowHint(GLFW_FOCUSED, false);
		
		// Flag Hidden
		if (m_Flags.Contains(Window::Flag::Hidden))
			glfwWindowHint(GLFW_VISIBLE, false);

		// Create Window
		m_Window = glfwCreateWindow(m_Layer->GetWidth(), m_Layer->GetHeight(), m_Name.c_str(), NULL, NULL);

		// Create Context
		m_Context = CreateReference<OpenGLRenderingContext>(m_Window);
		m_Context->Init();
		
		// Flag Iconified
		if (m_Flags.Contains(Window::Flag::Iconified))
			glfwIconifyWindow(m_Window);

		// \/ \/ \/ ---Infinite cursor mode.--- \/ \/ \/
		//glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		
		int x, y, width, height;
		glfwGetWindowPos(m_Window, &x, &y);
		glfwGetWindowSize(m_Window, &width, &height);
		m_Layer->SetSize({ width,height });
		Renderer::SetWindowSize((float)width, (float)height);
		m_TopLeft.x = x;
		m_TopLeft.y = y;

		// Monitor
		glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), nullptr, nullptr, &m_MonitorResolution.x, &m_MonitorResolution.y);

		if (!m_Window)
		{
			glfwTerminate();
			return;
		}
	}

	void Window::InitCallbacks()
	{
		glfwSetWindowUserPointer(m_Window, this);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* glfwWindow, int width, int height)
		{
			Window& window = *((Window*)glfwGetWindowUserPointer(glfwWindow));
			window.m_Layer->SetSize({ width,height });
			Renderer::SetWindowSize((float)width, (float)height);
			
			EventWindowSize event(vec2int(width,height));
			window.m_OnEventCallbackFn(event);
		});
		
		glfwSetWindowPosCallback(m_Window, [](GLFWwindow* glfwWindow, int x, int y)
		{
			Window& window = *((Window*)glfwGetWindowUserPointer(glfwWindow));
			window.m_TopLeft.x = x;
			window.m_TopLeft.y = y;

			EventWindowPosition event(vec2int(x,y));
			window.m_OnEventCallbackFn(event);
		});
		
		glfwSetWindowMaximizeCallback(m_Window, [](GLFWwindow* glfwWindow, int maximized)
		{
			Window& window = *((Window*)glfwGetWindowUserPointer(glfwWindow));
			if (maximized)
				window.m_Flags.Add(Window::Flag::Maximazed);
			else
				window.m_Flags.Remove(Window::Flag::Maximazed);
			HZ_WIN_TRACE("Window maximized ({})", maximized);
		});

		glfwSetWindowIconifyCallback(m_Window, [](GLFWwindow* glfwWindow, int iconified)
		{
			Window& window = *((Window*)glfwGetWindowUserPointer(glfwWindow));
			if (iconified)
				window.m_Flags.Add(Window::Flag::Iconified);
			else
				window.m_Flags.Remove(Window::Flag::Iconified);
			HZ_WIN_TRACE("Window iconified ({})", iconified);
		});

		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* glfwWindow, int focused)
		{
			Window& window = *((Window*)glfwGetWindowUserPointer(glfwWindow));
			if (focused)
				window.m_Flags.Add(Window::Flag::Focused);
			else
				window.m_Flags.Remove(Window::Flag::Focused);
			HZ_WIN_TRACE("Window focused ({})", focused);

			EventWindowFocus event((bool)focused);
			window.m_OnEventCallbackFn(event);
		});

	 // Keyboard Events
		glfwSetKeyCallback(m_Window, [](GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
		{
			Window& window = *((Window*)glfwGetWindowUserPointer(glfwWindow));
			if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
				if (window.m_Flags.Contains(Window::Flag::Maximazed))
					glfwRestoreWindow(window.m_Window);
			if (action == GLFW_PRESS && key == GLFW_KEY_F11)
				if (window.m_Flags.NotContains(Window::Flag::Maximazed))
					glfwMaximizeWindow(window.m_Window);

			EventKeyboardKey event((Keyboard::Key)key,(Keyboard::Action)action,(Keyboard::Modifier)mods);
			window.m_OnEventCallbackFn(event);
		});
		
		glfwSetCharCallback(m_Window, [](GLFWwindow* glfwWindow, unsigned int character)
		{
			Window& window = *((Window*)glfwGetWindowUserPointer(glfwWindow));

			EventKeyboardText event(character);
			window.m_OnEventCallbackFn(event);
		});

	 // Cursor Events
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* glfwWindow, double xpos, double ypos)
		{
			Window& window = *((Window*)glfwGetWindowUserPointer(glfwWindow));

			EventCursorPosition event(vec2(xpos,ypos));
			window.m_OnEventCallbackFn(event);

			// \/ \/ \/ ---To lock cursor at 0,0.--- \/ \/ \/
			//glfwSetCursorPos(window.m_Window,0.0,0.0);
		});
		
		glfwSetCursorEnterCallback(m_Window, [](GLFWwindow* glfwWindow, int entered)
		{
			Window& window = *((Window*)glfwGetWindowUserPointer(glfwWindow));

			EventCursorEntry event(entered);
			window.m_OnEventCallbackFn(event);
		});

	 // Mouse Events
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* glfwWindow, int button, int action, int mods)
		{
			Window& window = *((Window*)glfwGetWindowUserPointer(glfwWindow));

			EventMouseButton event((Mouse::Button)button,(Mouse::Action)action,(Keyboard::Modifier)mods);
			window.m_OnEventCallbackFn(event);
		});
		
		glfwSetScrollCallback(m_Window, [](GLFWwindow* glfwWindow, double xoffset, double yoffset)
		{
			Window& window = *((Window*)glfwGetWindowUserPointer(glfwWindow));

			EventMouseScroll event(vec2(xoffset, yoffset));
			window.m_OnEventCallbackFn(event);
		});
	}

	void Window::Run()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}
	
	void Window::SetPosition(int width, int height)
	{
		vec2int resolutionCap = m_MonitorResolution - 50;
		int w, h;

		if (width > resolutionCap.x)
			w = resolutionCap.x;
		else if (width < 0)
			w = 0;
		else
			w = width;

		if (height > resolutionCap.y)
			h = resolutionCap.y;
		else if (height < 0)
			h = 0;
		else
			h = height;

		glfwSetWindowPos(m_Window, w, h);
	}

	void Window::SetSize(int width, int height)
	{
		glfwSetWindowSize(m_Window, width, height);
	}

	void Window::CenterWindow()
	{
		// Set Up Position
		glfwSetWindowPos(m_Window,
			(m_MonitorResolution.x / 2) - (m_Layer->GetWidth() / 2),
			(m_MonitorResolution.y / 2) - (m_Layer->GetHeight() / 2));
	}

	void Window::SetTitle(const std::string& title)
	{
		glfwSetWindowTitle(m_Window, title.c_str());
	}

	void Window::Minimize()
	{
		glfwIconifyWindow(m_Window);
	}

	void Window::Resume()
	{
		glfwRestoreWindow(m_Window);
	}

	int Window::IsAlive()
	{
		return !glfwWindowShouldClose(m_Window);
	}

	void Window::Close()
	{
		glfwSetWindowShouldClose(m_Window,true);
	}

}
