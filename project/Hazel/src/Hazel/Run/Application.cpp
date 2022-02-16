#include "pch.h"
#include "Application.h"

#include "Graphics/Renderer/Renderer.h"

namespace Hazel 
{

	Application::Application(const std::string& name,  Window::Flags flags)
	{
		HZ_APP_TRACE("Initializing {0}... ", name);

		m_Window = CreateReference<Window>(name, flags);

		m_Window->Init();
		
		m_Window->SetOnEventCallback([this](const Event& e) { return OnEvent(e); });
		m_Window->InitCallbacks();
		m_Window->CenterWindow();

		Renderer::Init();

		m_dt = m_dt_timer.update().count();
	}

	Application::~Application()
	{
		OnShutdown();
		glfwTerminate();
	}

	void Application::Run()
	{
		HZ_APP_TRACE("Start running ... ");
		OnInit();

	 // Loop until the user closes the window
		while (m_Window->IsAlive()) {

			m_dt = m_dt_timer.update().count();

			m_Window->Run();

			OnUpdate();
		}
		HZ_APP_TRACE(" ... Stop running!");
	}

}
