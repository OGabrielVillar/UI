#include "pch.h"

#include "Log.h"

#if _CONSOLEAPP

namespace Hazel {
	
		Reference<spdlog::logger> Log::s_EngineLogger;

}

#endif
