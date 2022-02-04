#pragma once
#include "TimeLiterals.h"

namespace Hazel::Time {

	using namespace Time::Literals;

	using nanoseconds = std::chrono::duration<float, std::nano>;
	using microseconds = std::chrono::duration<float, std::micro>;
	using milliseconds = std::chrono::duration<float, std::milli>;
	using seconds = std::chrono::duration<float>;
	using minutes = std::chrono::duration<float,std::ratio<60>>;
	using hours   = std::chrono::duration<float,std::ratio<3600>>;

}
