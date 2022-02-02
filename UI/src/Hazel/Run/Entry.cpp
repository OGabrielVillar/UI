#include "pch.h"

#include "../Graphics/Graphics.h"

#include "Log.h"
#include "Application.h"
#include "Graphics/Renderer/BufferLayout.h"

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

struct Vertex {
	float x,y,z;
};


template <class _CharT, class _Traits>
std::basic_ostream<_CharT, _Traits>& operator<<(
    std::basic_ostream<_CharT, _Traits>& _Os, const Vertex& vertex) {
    return _Os << "[x:" << vertex.x << " y:" << vertex.y << " z:" << vertex.z << "]";
}

int APP 
{
	using namespace Hazel;

	HZ_INIT_LOG;
	Hazel::Application app;

	app.Run();

}
