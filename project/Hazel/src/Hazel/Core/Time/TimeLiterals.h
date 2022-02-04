#pragma once

#include "pch.h"

namespace Hazel::Time::Literals 
{

	_NODISCARD constexpr _CHRONO hours operator"" _hours(unsigned long long _Val) noexcept /* strengthened */ {
		return _CHRONO hours(_Val);
	}
	_NODISCARD constexpr _CHRONO duration<double, std::ratio<3600>> operator"" _hours(long double _Val) noexcept
	/* strengthened */ {
		return _CHRONO duration<double, std::ratio<3600>>(_Val);
	}
	_NODISCARD constexpr _CHRONO minutes(operator"" _minutes)(unsigned long long _Val) noexcept /* strengthened */ {
		return _CHRONO minutes(_Val);
	}
	_NODISCARD constexpr _CHRONO duration<double, std::ratio<60>>(operator"" _minutes)(long double _Val) noexcept
	/* strengthened */ {
		return _CHRONO duration<double, std::ratio<60>>(_Val);
	}
	_NODISCARD constexpr _CHRONO seconds operator"" _seconds(unsigned long long _Val) noexcept /* strengthened */ {
		return _CHRONO seconds(_Val);
	}
	_NODISCARD constexpr _CHRONO duration<double> operator"" _seconds(long double _Val) noexcept /* strengthened */ {
		return _CHRONO duration<double>(_Val);
	}
	_NODISCARD constexpr _CHRONO milliseconds operator"" _milliseconds(unsigned long long _Val) noexcept /* strengthened */ {
		return _CHRONO milliseconds(_Val);
	}
	_NODISCARD constexpr _CHRONO duration<double, std::milli> operator"" _milliseconds(long double _Val) noexcept
	/* strengthened */ {
		return _CHRONO duration<double, std::milli>(_Val);
	}
	_NODISCARD constexpr _CHRONO microseconds operator"" _microseconds(unsigned long long _Val) noexcept /* strengthened */ {
		return _CHRONO microseconds(_Val);
	}
	_NODISCARD constexpr _CHRONO duration<double, std::micro> operator"" _microseconds(long double _Val) noexcept
	/* strengthened */ {
		return _CHRONO duration<double, std::micro>(_Val);
	}
	_NODISCARD constexpr _CHRONO nanoseconds operator"" _nanoseconds(unsigned long long _Val) noexcept /* strengthened */ {
		return _CHRONO nanoseconds(_Val);
	}
	_NODISCARD constexpr _CHRONO duration<double, std::nano> operator"" _nanoseconds(long double _Val) noexcept
		/* strengthened */ {
		return _CHRONO duration<double, std::nano>(_Val);
	}

}
