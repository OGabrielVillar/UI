#pragma once

#ifdef HZ_PLATFORM_WINDOWS

#if _CONSOLEAPP
	#define APP main()
#else
	#define APP WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif

namespace Hazel {
	extern Application* CreateApplication();
}
bool g_ApplicationRunning = true;

int APP
{

	HZ_INIT_LOG;

	Hazel::Application* app = Hazel::CreateApplication();

	app->Run();
	
	delete app;

	HZ_APP_INFO(R"(
=================================================================
|                                                               |
|                                                               |
|       [en] --- THANK YOU FOR TESTING OUT MY GAME! ---         |
|                 Dream on, always!                             |
|                                                               |
|       [pt] --- OBRIGADO POR TESTAR MEU JOGO! ---              |
|                 Sonhe, sempre!                                |
|                                                               |
|                                      by Gabriel Villar        |
|                                          ig @_gvillar_        |
|                                                               |
=================================================================
	)");
	std::cin.get();

}

#endif
