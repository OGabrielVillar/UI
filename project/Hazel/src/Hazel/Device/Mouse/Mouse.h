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
	};
	
	struct EventMouseScroll : Event {
		EventMouseScroll(const vec2& offset_in = { 0.f, 0.f })
			: Event(EventType::MouseScroll), offset(offset_in)
		{}
		inline bool operator==(const EventMouseScroll& other) const { return true; }
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
