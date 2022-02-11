#pragma once

#include "MouseCodes.h"
#include "Device/Keyboard/Keyboard.h"

#include "Core/Flags.h"
#include "Input/Event.h"

namespace Hazel 
{
	class Mouse {
	public:
		using Button = MouseCode;
		using Action = MouseAction;
		CursorMode cursorMode;
	};

	struct EventCursorPosition : Event {
		EventCursorPosition(vec2 position_in = { 0.f , 0.f })
			: Event(EventType::CursorPosition), position(position_in)
		{}
		inline bool operator==(const EventCursorPosition& other) const { return true; }
		inline static EventType GetType() { return EventType::CursorPosition; }
		vec2 position;
	};
	struct EventCursorEntry : Event {
		EventCursorEntry(bool entered_in)
			: Event(EventType::CursorEntry), entered(entered_in)
		{}
		inline bool operator==(const EventCursorEntry& other) const { return entered == other.entered; }
		inline static EventType GetType() { return EventType::CursorEntry; }
		bool entered;
	};
	
	struct EventMouseScroll : Event {
		EventMouseScroll(const vec2& offset_in)
			: Event(EventType::MouseScroll), offset(offset_in)
		{}
		inline bool operator==(const EventMouseScroll& other) const { return offset == other.offset; }
		inline static EventType GetType() { return EventType::MouseScroll; }
		vec2 offset;
	};
	struct EventMouseButton : Event {
		EventMouseButton(Mouse::Button button, Mouse::Action action, Keyboard::Modifier modifier = Keyboard::Modifier())
			: Event(EventType::MouseButton), button(button), action(action), modifier(modifier)
		{}
		inline bool operator==(const EventMouseButton& other) const { 
			return button == other.button && action == other.action && modifier == other.modifier; 
		}
		inline static EventType GetType() { return EventType::MouseButton; }
		Mouse::Button button;
		Mouse::Action action;
		Keyboard::Modifier modifier;
	};

}
