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

		seconds get() {
			return m_time;
		}

	private:
		seconds m_time = 0.0seconds;
		std::chrono::steady_clock::time_point last;
	};

}
