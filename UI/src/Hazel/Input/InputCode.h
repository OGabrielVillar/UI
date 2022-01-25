#pragma once

#include "Device/InputDevice.h"
#include "Device/KeyboardCodes.h"
#include "Device/MouseCodes.h"

template <typename E>
constexpr typename std::underlying_type<E>::type to_underlying(E e) noexcept {
	return static_cast<typename std::underlying_type<E>::type>(e);
}

namespace Hazel 
{
	struct InputCode {

		InputCode()
			: device(InputDevice::Undefined), code(0)
		{}

		InputCode(KeyCode code_in) 
			: code(to_underlying(code_in)), 
			  device(InputDevice::Keyboard)
		{}

		InputCode(MouseCode code_in)
			: code(to_underlying(code_in)), 
			  device(InputDevice::Mouse)
		{}

		bool operator == (const InputCode& other) const {
			return device == other.device && code == other.code;
		}

		InputDevice device;
		unsigned int code;
	};


}