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

int APP
{
	auto a0 = random_rgba();
	auto a1 = random_rgba();
	auto a2 = random_rgba();
	auto a3 = random_rgba();
	auto a4 = random_rgba();

	HZ_INIT_LOG;

	Hazel::Application app;

	auto& w1 = app.CreateWindow("Modesto");
	w1.SetColor(random_rgba());

	std::this_thread::sleep_for(Hazel::Time::seconds(0.5));
	// TODO: Remover essa linha causa a thread do "Humildo" inicie junto com a do "Modesto", causando problemas no Glad/GLFW;

	auto& w2 = app.CreateWindow("Humildo");
	w2.SetColor(random_rgba());

	std::this_thread::sleep_for(Hazel::Time::seconds(0.5));
	// TODO: Remover essa linha causa a thread do app a checar por funções do Glad/GLFW mais rápido do que a janela do humildo se inicia;
	
	auto& w3 = app.CreateWindow("Humildo");
	w3.SetColor(random_rgba());

	std::this_thread::sleep_for(Hazel::Time::seconds(0.5));
	// TODO: Remover essa linha causa a thread do app a checar por funções do Glad/GLFW mais rápido do que a janela do humildo se inicia;
	
	auto& w4 = app.CreateWindow("Humildo");
	w4.SetColor(random_rgba());

	std::this_thread::sleep_for(Hazel::Time::seconds(0.5));
	// TODO: Remover essa linha causa a thread do app a checar por funções do Glad/GLFW mais rápido do que a janela do humildo se inicia;

	app.Run();
}
