#pragma once

#include "Core/Time/Timer.h"

#ifdef HZ_DEBUG
	#define _CONSOLEAPP 1
#elif HZ_RELEASE
	#define _CONSOLEAPP 1
#else
	#define _WINDOWEDAPP 1
#endif

namespace Hazel {

	class Profile {
	private:
		inline static std::stringstream s_Profiler;

	public:
		inline static std::string Get(){
			std::string str = s_Profiler.str();
			Clear();
			return str;
		}
		inline static void Clear(){
			s_Profiler = std::stringstream();
		}

		Profile(const std::string& name, bool print_fps = false) 
			: m_Name(name),
			  m_PrintFPS(print_fps)
		{}

		~Profile() 
		{
			Time::seconds secs = m_Timer.update();
			if (m_PrintFPS)
				s_Profiler << "\n    [" << m_Name 
				<< "]\n        ms: " << std::to_string(Time::milliseconds(secs).count()) 
				<< ".\n        fps:" << std::to_string(1.f / secs.count()) << ".";
			else
				s_Profiler << "\n    [" << m_Name 
				<< "]\n        ms: " << std::to_string(Time::milliseconds(secs).count()) << ".";
		}

	private:
		bool m_PrintFPS = false;
		std::string m_Name;
		Time::Timer m_Timer;
	};

#ifdef _CONSOLEAPP

#define PROFILE(x) Profile profiling(x)
#define PROFILE_FPS(x) Profile profiling(x, true)
#define PRINT_PROFILE() std::cout << "\n[PROFILE]" << Profile::Get() << std::endl << std::endl
#define CLEAR_PROFILE() Profile::Clear()

#else

#define PROFILE(x)
#define PROFILE_FPS(x)
#define PRINT_PROFILE()
#define CLEAR_PROFILE()

#endif
}
