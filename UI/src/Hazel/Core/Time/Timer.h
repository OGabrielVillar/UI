#pragma once

#include "TimeCommon.h"

namespace Hazel::Time {

	class Timer {
	public:
		Timer() : last(std::chrono::steady_clock::now()) {}
		

		operator float() const {
			return m_time.count();
		}

		seconds update() {
			const auto old = last;
			last = std::chrono::steady_clock::now();
			m_time = last - old;
			return m_time;
		}

		seconds get() const {
			return m_time;
		}

	private:
		seconds m_time = 0.0_seconds;
		std::chrono::steady_clock::time_point last;
	};

	    template <class _CharT, class _Traits>
    std::basic_ostream<_CharT, _Traits>& operator<<(
        std::basic_ostream<_CharT, _Traits>& _Os, const Timer& timer) {
        return _Os << timer.get();
    }


}
