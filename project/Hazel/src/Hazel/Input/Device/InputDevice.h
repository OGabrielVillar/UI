#pragma once

namespace Hazel {

	enum class InputDevice : unsigned char
	{
		Undefined = 0,
		System    = 1,
		Keyboard  = 2,
		Mouse     = 3,
		Joystick  = 4
	};

	enum class InputAction : uint8_t {
		Undefined,
		SystemWindowClose,
		SystemWindowFocus,
		SystemWindowLostFocus,
		SystemWindowMove,
		SystemWindowResize,
		SystemAppTick,
		SystemAppUpdate,
		SystemAppRender,
		KeyboardKeyPress,
		KeyboardKeyRelease,
		KeyboardKeyType,
		MouseButtonPress,
		MouseButtonRelease,
		MouseMove,
		MouseScroll
	};

}