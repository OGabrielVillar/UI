#pragma once

namespace std {
	template<class _CharT, class _Traits>
	class basic_ostream;
}

using uint16_t = unsigned short;

namespace Hazel {

	enum class MouseAction : uint8_t
	{
		Release = 0,
		Press = 1,
		Repeat = 2
	};

	enum class MouseCode : uint16_t
	{
		Button0     = 0,
		Button1     = 1,
		Button2     = 2,
		Button3     = 3,
		Button4     = 4,
		Button5     = 5,
		Left        = Button0,
		Right       = Button1,
		Middle      = Button2,
	};

	template <class _CharT, class _Traits>
    inline std::basic_ostream<_CharT, _Traits>& operator<<(
        std::basic_ostream<_CharT, _Traits>& _Os, MouseCode button) {
        return _Os << (uint16_t)button;
    }

}

// From glfw3.h
#define HZ_MOUSE_BUTTON_LEFT    0
#define HZ_MOUSE_BUTTON_RIGHT   1
#define HZ_MOUSE_BUTTON_MIDDLE  2
