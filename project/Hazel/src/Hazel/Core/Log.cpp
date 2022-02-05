#include "pch.h"

#include "Log.h"

#ifdef _CONSOLEAPP

namespace Hazel {
	
		std::shared_ptr<spdlog::logger> Log::s_ApplicationLogger;
		std::shared_ptr<spdlog::logger> Log::s_WindowLogger;
		std::shared_ptr<spdlog::logger> Log::s_Logger;

}

#endif
