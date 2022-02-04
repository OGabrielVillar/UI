#pragma once

namespace Hazel {

	enum class CursorMode
	{
		Normal = 0,
		Hidden = 1,
		Locked = 2
	};

	enum class MouseButtonCode : uint16_t
	{
		Button0  = 0,
		Button1  = 1,
		Button2  = 2,
		Button3  = 3,
		Button4  = 4,
		Button5  = 5,
		Left     = Button0,
		Right    = Button1,
		Middle   = Button2
	};


	inline std::ostream& operator<<(std::ostream& os, MouseButtonCode button)
	{
		os << static_cast<int32_t>(button);
		return os;
	}

}

// From glfw3.h
#define HZ_MOUSE_BUTTON_LEFT    0
#define HZ_MOUSE_BUTTON_RIGHT   1
#define HZ_MOUSE_BUTTON_MIDDLE  2