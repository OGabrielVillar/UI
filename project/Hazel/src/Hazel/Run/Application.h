#pragma once

#include "Window.h"

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

	 protected:
		Timer m_dt_timer;
		float m_dt;
		Reference<Window> m_Window;
	};

}
