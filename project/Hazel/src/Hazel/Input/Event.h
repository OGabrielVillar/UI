#pragma once

namespace Hazel 
{
	
	//enum class Any : uint8_t;
	enum class EventType : int8_t {
		None = 0,
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

	enum class TriggerFlag : uint8_t {
		Any = BIT(0)
	};

	// --------------------
	// --- Trigger Type ---
	// --------------------

	struct TriggerType {
		using Flag = TriggerFlag;
		using Flags = Flags<TriggerFlag>;
		using underlying_t = std::underlying_type_t<EventType>;

		using enum EventType;

		TriggerType() = default;
		TriggerType(EventType input) : m_Value((underlying_t)input) {}
		TriggerType(const TriggerType& other) = default;
		inline TriggerType& operator = (TriggerType other) { m_Value = other.m_Value; return *this; }
		inline TriggerType& operator = (underlying_t other) { m_Value = other; return *this; }
		inline TriggerType& operator = (Flag other) { m_Flags = other; return *this;  }
		inline bool operator == (EventType other) const
		{ 
			if (m_Flags.Contains(Flag::Any))
				return true;
			return m_Value == (underlying_t)other; 
		}

	private:
		underlying_t m_Value = 0;
		Flags m_Flags;
	};

	// ---------------------
	// --- Window Events ---
	// ---------------------

	struct EventWindowSize : Event {
		EventWindowSize(const vec2int& size = { 0.f , 0.f })
			: Event(EventType::WindowSize), size(size)
		{}
		inline bool operator==(const EventWindowSize& other) const { return true; }
		inline static EventType GetType() { return EventType::WindowSize; }
		vec2int size;
	};

	struct EventWindowPosition : Event {
		EventWindowPosition(const vec2int& position = { 0.f , 0.f })
			: Event(EventType::WindowPosition), position(position)
		{}
		inline bool operator==(const EventWindowPosition& other) const { return true; }
		inline static EventType GetType() { return EventType::WindowPosition; }
		vec2int position;
	};

	struct EventWindowFocus : Event {
		EventWindowFocus(bool focused = true)
			: Event(EventType::WindowFocus), focused(focused)
		{}
		inline bool operator==(const EventWindowFocus& other) const { return true; }
		inline static EventType GetType() { return EventType::WindowFocus; }
		bool focused;
	};
}
