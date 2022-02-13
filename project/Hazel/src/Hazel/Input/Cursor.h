#pragma once

#include "Event.h"

namespace Hazel {

	enum class CursorMode : uint8_t {
		Normal,
		Hidden,
		Disabled,
		Locked,
	};

	struct Cursor 
	{
		using Mode = CursorMode;
		Mode mode;
	};

	// --- Events ---

	struct EventCursorPosition : Event 
	{
		EventCursorPosition(vec2 position_in = { 0.f , 0.f })
			: Event(EventType::CursorPosition), position(position_in)
		{}
		inline bool operator==(const EventCursorPosition& other) const { return true; }
		inline static EventType GetType() { return EventType::CursorPosition; }
		vec2 position;
	};
	struct EventCursorEntry : Event 
	{
		EventCursorEntry(bool entered_in)
			: Event(EventType::CursorEntry), entered(entered_in)
		{}
		inline bool operator==(const EventCursorEntry& other) const { return entered == other.entered; }
		inline static EventType GetType() { return EventType::CursorEntry; }
		bool entered;
	};

}
