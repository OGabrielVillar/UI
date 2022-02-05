#pragma once

namespace Hazel 
{

	enum class EventType : uint8_t {
		WindowSize,
		WindowFocus,
		WindowPosition,
		CursorPosition,
		CursorEntry,
		MouseButton,
		MouseScroll,
		KeyboardKey,
		KeyboardText,
	};

	struct Event {
		Event(EventType type)
			: type(type)
		{}
		EventType type;
	};

	using EventCallbackFn = std::function<bool(const Event&)>;

}
