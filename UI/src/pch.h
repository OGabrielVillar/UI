#pragma once

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <memory>
#include <thread>
#include <mutex>
#include <deque>
#include <optional>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdint>
#include <cmath>
#include <utility>
#include <stack>
#include <array>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include <entt/entt.hpp>


#ifdef _WINDOWS
 #include <Windows.h>
#endif
#undef CreateWindow

//#ifdef _WIN32
//#define _WIN32_WINNT 0x0A00
//#endif

//#define ASIO_STANDALONE
//#pragma warning( push, 0 )
//#include <asio.hpp>
//#include <asio/ts/buffer.hpp>
//#include <asio/ts/internet.hpp>
//#pragma warning( pop )

//#include <stb_image.h>
//#include <stb_textedit.h>
//#include <stb_truetype.h>

#if _DEBUG
	#define _CONSOLEAPP TRUE
#elif _RELEASE
	#define _CONSOLEAPP TRUE
#else
	#define _WINDOWEDAPP TRUE
#endif

#if _CONSOLEAPP
	#define FMT_USE_USER_DEFINED_LITERALS 0
	#include <spdlog/spdlog.h>
	#include <spdlog/sinks/stdout_color_sinks.h>
#endif

namespace Hazel {

	#define BIT(x) 1 << x

	// Pointers
		template<typename T>
		using Scope = std::unique_ptr<T>;
		
		template<typename T, typename ... Args>
		constexpr Scope<T> CreateScope(Args&& ... args)
		{
			return std::make_unique<T>(std::forward<Args>(args)...);
		}

		template<typename T>
		using Reference = std::shared_ptr<T>;
		
		template<typename T, typename ... Args>
		constexpr Reference<T> CreateReference(Args&& ... args)
		{
			return std::make_shared<T>(std::forward<Args>(args)...);
		}

}
