#include "pch.h"

#include "../Graphics/Graphics.h"

#include "Log.h"
#include "Application.h"

#if _CONSOLEAPP
	#define APP main()
#else
	#define APP WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif

float random_algo() { 
	auto& inst = Hazel::Math::_internals::_Random::get_instance();
	return inst.Float() * 1.0f + 0.0f; 
}

Hazel::rgba random_rgba() {
	return Hazel::rgba(random_algo(),random_algo(),random_algo(),1.f);
}

Hazel::Application& CreateRandomWindows(unsigned char many_windows, Hazel::Application& app) 
{
	unsigned char many_windows_capped = many_windows;
	many_windows_capped > 8 ? many_windows_capped = 3 : many_windows_capped;

	for (size_t i = 0; i < many_windows_capped; i++)
	{

		auto& w = app.CreateWindow(std::to_string(i).c_str());
		w.SetColor(random_rgba());

		std::this_thread::sleep_for(Hazel::Time::seconds(0.5));
		// TODO: Remover essa linha causa a thread de uma criação inicie junto com a de outro, causando problemas no Glad/GLFW;

	}
	return app;
}

int APP
{
	using namespace Hazel;

	HZ_INIT_LOG;

	Hazel::Application app;
	
	auto& window0 = app.CreateWindow("Hazel");

	std::this_thread::sleep_for(Hazel::Time::seconds(0.5));

	app.Run();
}
