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

	struct CursorPositionEvent : Event {
		CursorPositionEvent(vec2 position_in)
			: Event(EventType::CursorPosition), position(position_in)
		{}
		inline bool operator==(const CursorPositionEvent& other) const { return true; }
		vec2 position;
	};
	struct CursorEntryEvent : Event {
		CursorEntryEvent(bool entered_in)
			: Event(EventType::CursorEntry), entered(entered_in)
		{}
		inline bool operator==(const CursorEntryEvent& other) const { return entered == other.entered; }
		bool entered;
	};
	
	struct MouseScrollEvent : Event {
		MouseScrollEvent(const vec2& offset_in)
			: Event(EventType::MouseScroll), offset(offset_in)
		{}
		inline bool operator==(const MouseScrollEvent& other) const { return offset == other.offset; }
		vec2 offset;
	};
	struct MouseButtonEvent : Event {
		MouseButtonEvent(Mouse::Button button, Mouse::Action action, Keyboard::Modifier modifier = Keyboard::Modifier())
			: Event(EventType::MouseButton), button(button), action(action), modifier(modifier)
		{}
		inline bool operator==(const MouseButtonEvent& other) const { 
			
			return button == other.button && action == other.action && modifier == other.modifier; 
		
		}
		Mouse::Button button;
		Mouse::Action action;
		Keyboard::Modifier modifier;
	};

}
