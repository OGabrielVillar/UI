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
	inline bool compare_buffers(const uint8_t* buff_a, const uint8_t* buff_b, int buffer_size) {
		for (size_t i = 0; i < buffer_size; i++)
		{
			if (buff_a[i] != buff_b[i])
				return false;
		}
		return true;
	}

#define INPUT_SIGNAL_BUFF_SIZE 8 
	// 8 bits for now, to accomodate the size of two floats in a movement or scroll signals.

	template<
		class T,
		typename = typename std::enable_if<sizeof(T) <= INPUT_SIGNAL_BUFF_SIZE>
	>
	struct _InputT {
		_InputT()
			: device(InputDevice::Undefined), action(InputAction::Undefined)
		{}

		_InputT(InputDevice device_in, InputAction action_in, T value_in)
			: device(device_in), action(action_in), value(value_in)
		{}

		InputAction action;
		InputDevice device;
		T value;
	};
	const int sizze = sizeof(glm::vec4);
	using InputCode = _InputT<uint16_t>;
	using InputMovement = _InputT<glm::vec4>;
	using InputScroll = _InputT<glm::vec2>;

	struct InputSignal {

		InputSignal()
			: action(InputAction::Undefined)
		{}
		InputSignal(const InputSignal&) = default;

		template <class T>
		InputSignal(const _InputT<T>& other) :
			action(other.action)
		{
			memcpy(buffer, &other.value, sizeof(T));
		}

		InputSignal(KeyCode keyCode_in, InputAction action_in)
			: action(action_in)
		{
			memcpy(buffer,&keyCode_in,sizeof(KeyCode));
		}

		InputSignal(MouseButtonCode mouseButton_in, InputAction action_in)
			: action(action_in)
		{
			memcpy(buffer, &mouseButton_in, sizeof(MouseButtonCode));
		}

		template <
			class T,
			typename = typename std::enable_if<sizeof(T) <= INPUT_SIGNAL_BUFF_SIZE>
		>
		InputSignal(InputAction action_in, T value_in)
			: action(action_in)
		{
			memcpy(buffer, &value_in, sizeof(T));
		}

		InputSignal(InputAction action_in)
			: action(action_in)
		{}




		bool operator == (const InputSignal& other) const 
		{
		if (to_underlying(action) <= 4)
			return action == other.action && compare_buffers(buffer, other.buffer, INPUT_SIGNAL_BUFF_SIZE);
		else
			return action == other.action;
		}

		InputAction action;
		uint8_t buffer[INPUT_SIGNAL_BUFF_SIZE] = {};
	};

}