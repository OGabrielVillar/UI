#pragma once

#include "core.h"


#ifdef _CONSOLEAPP

namespace Hazel {
	class Log {
	private:
		Log() = delete;
		
	public:
		inline static void Init() {
			std::cout << "[  Time  |  Origin  ] Log initialized!" << std::endl;
			spdlog::set_pattern("%^[%T|%n] %v%$");
			s_ApplicationLogger = spdlog::stdout_color_mt("Application");
			s_ApplicationLogger->set_level(spdlog::level::trace);

			s_WindowLogger = spdlog::stdout_color_mt("Window");
			s_WindowLogger->set_level(spdlog::level::trace);
			
			s_Logger = spdlog::stdout_color_mt("Hazel");
			s_Logger->set_level(spdlog::level::trace);
		}

		inline static Reference<spdlog::logger>& GetAppLogger() { return s_ApplicationLogger; }
		inline static Reference<spdlog::logger>& GetWinLogger() { return s_WindowLogger; }
		inline static Reference<spdlog::logger>& GetLogger() { return s_Logger; }
	private:
		static Reference<spdlog::logger> s_ApplicationLogger;
		static Reference<spdlog::logger> s_WindowLogger;
		static Reference<spdlog::logger> s_Logger;
	};
}

#define HZ_ENABLE_ASSERTS

#define HZ_INIT_LOG Hazel::Log::Init()

#define HZ_APP_TRACE(...) Hazel::Log::GetAppLogger()->trace(__VA_ARGS__)
#define HZ_APP_INFO(...) Hazel::Log::GetAppLogger()->info(__VA_ARGS__)
#define HZ_APP_WARN(...) Hazel::Log::GetAppLogger()->warn(__VA_ARGS__)
#define HZ_APP_ERROR(...) Hazel::Log::GetAppLogger()->error(__VA_ARGS__)
#define HZ_APP_FATAL(...) Hazel::Log::GetAppLogger()->critical(__VA_ARGS__)


#define HZ_WIN_TRACE(...) Hazel::Log::GetWinLogger()->trace(__VA_ARGS__)
#define HZ_WIN_INFO(...) Hazel::Log::GetWinLogger()->info(__VA_ARGS__)
#define HZ_WIN_WARN(...) Hazel::Log::GetWinLogger()->warn(__VA_ARGS__)
#define HZ_WIN_ERROR(...) Hazel::Log::GetWinLogger()->error(__VA_ARGS__)
#define HZ_WIN_FATAL(...) Hazel::Log::GetWinLogger()->critical(__VA_ARGS__)

#define HZ_ERROR(...) Hazel::Log::GetLogger()->error(__VA_ARGS__)

#else

#define HZ_INIT_LOG
	
#define HZ_APP_TRACE(...)
#define HZ_APP_INFO(...)
#define HZ_APP_WARN(...)
#define HZ_APP_ERROR(...)
#define HZ_APP_FATAL(...)
#define HZ_APP_ASSERT(x,...)

#define HZ_WIN_TRACE(...)
#define HZ_WIN_INFO(...)
#define HZ_WIN_WARN(...)
#define HZ_WIN_ERROR(...)
#define HZ_WIN_FATAL(...)
#define HZ_WIN_ASSERT(x,...)

#endif

#ifdef HZ_ENABLE_ASSERTS

#define HZ_EXPAND_VARGS(x) x
#define HZ_ASSERT_NO_MESSAGE(condition) { if(!(condition)) { HZ_ERROR("Assertion Failed"); __debugbreak(); } }
#define HZ_ASSERT_MESSAGE(condition, ...) { if(!(condition)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define HZ_ASSERT_RESOLVE(arg1, arg2, macro, ...) macro
#define HZ_GET_ASSERT_MACRO(...) HZ_EXPAND_VARGS(HZ_ASSERT_RESOLVE(__VA_ARGS__, HZ_ASSERT_MESSAGE, HZ_ASSERT_NO_MESSAGE))
#define HZ_ASSERT(...) HZ_EXPAND_VARGS( HZ_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )

#else

#define HZ_ERROR(...)
#define HZ_ASSERT(...)

#endif
