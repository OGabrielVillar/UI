#pragma once

#include "core.h"


#if _CONSOLEAPP

namespace Hazel {
	class Log {
	private:
		Log() = delete;
		
	public:
		inline static void Init() {
			spdlog::set_pattern("%^[%T] %n: %v%$");
			s_EngineLogger = spdlog::stdout_color_mt("HAZEL");
			s_EngineLogger->set_level(spdlog::level::trace);
			s_EngineLogger->warn("Log Initialization!");
		}

		inline static Reference<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
	private:
		static Reference<spdlog::logger> s_EngineLogger;
	};
}

#define HZ_INIT_LOG Hazel::Log::Init()

#define HZ_TRACE(...) Hazel::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define HZ_INFO(...) Hazel::Log::GetEngineLogger()->info(__VA_ARGS__)
#define HZ_WARN(...) Hazel::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define HZ_ERROR(...) Hazel::Log::GetEngineLogger()->error(__VA_ARGS__)
#define HZ_FATAL(...) Hazel::Log::GetEngineLogger()->error(__VA_ARGS__)
#define HZ_ASSERT(x,...) if(x) \
	Hazel::Log::GetEngineLogger()->error(__VA_ARGS__)

#else

#define HZ_INIT_LOG
	
#define HZ_TRACE(...)
#define HZ_INFO(...)
#define HZ_WARN(...)
#define HZ_ERROR(...)
#define HZ_FATAL(...)
#define HZ_ASSERT(x,...)

#endif
