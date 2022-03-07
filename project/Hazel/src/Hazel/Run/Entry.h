#pragma once

#ifdef HZ_PLATFORM_WINDOWS

#ifdef _CONSOLEAPP
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

#ifdef _CONSOLEAPP
	std::cout << (R"(
=================================================================
|                                                               |
|                       VOID GAME ENGINE                        |
|                                                               |
|                        version: 0.0.16                        |
|                                                               |
=================================================================
	)") << std::endl;
#endif

	HZ_INIT_LOG;

	Hazel::Application* app = Hazel::CreateApplication();

	app->Run();
	
	delete app;

	HZ_APP_INFO(R"(
=================================================================
|                                                               |
|       [en] --- THANK YOU FOR TESTING OUT MY GAME! ---         |
|                                                               |
|       [pt] --- OBRIGADO POR TESTAR MEU JOGO! ---              |
|                                                               |
|                                      by Gabriel Villar        |
|                                          ig @_gvillar_        |
|                                                               |
=================================================================
(press any key to exit))");
	std::cin.get();

}

#endif
