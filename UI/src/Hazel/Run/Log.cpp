#include "pch.h"

#include "Log.h"

#if _CONSOLEAPP

namespace Hazel {
	
		Reference<spdlog::logger> Log::s_ApplicationLogger;
		Reference<spdlog::logger> Log::s_WindowLogger;
		Reference<spdlog::logger> Log::s_Logger;

}

#endif
