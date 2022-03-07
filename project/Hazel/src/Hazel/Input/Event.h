#pragma once

#include "Device/Keyboard/Keyboard.h"
#include "Device/Mouse/Mouse.h"
#include "Cursor.h"

namespace Hazel 
{
	
	//enum class Any : uint8_t;
	enum class EventType : int8_t {
		None = 0,
		WindowSize,
		WindowPosition,
		WindowFocus,
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

	// ---------------------
	// --- Window Events ---
	// ---------------------

	struct EventWindowSize : Event {
		EventWindowSize(const vec2int& size = { 0.f , 0.f })
			: Event(EventType::WindowSize), size(size)
		{}
		vec2int size;
	};

	struct EventWindowPosition : Event {
		EventWindowPosition(const vec2int& position = { 0.f , 0.f })
			: Event(EventType::WindowPosition), position(position)
		{}
		vec2int position;
	};

	struct EventWindowFocus : Event {
		EventWindowFocus(bool focused = true)
			: Event(EventType::WindowFocus), focused(focused)
		{}
		bool focused;
	};

	// -----------------------
	// --- Keyboard Events ---
	// -----------------------

	struct EventKeyboardKey : Event {
		EventKeyboardKey(Keyboard::Key key, Keyboard::Action action, Keyboard::Modifier modifier = Keyboard::Modifier())
			: Event(EventType::KeyboardKey), key(key), action(action), modifier(modifier)
		{}
		inline static EventType GetType() { return EventType::KeyboardKey; }

		Keyboard::Key key;
		Keyboard::Modifier modifier;
		Keyboard::Action action;
	};

	struct EventKeyboardText : Event {
		EventKeyboardText(uint32_t character)
			: Event(EventType::KeyboardText), character(character)
		{}
		uint32_t character;
		/* LFW supports text input in the form of a stream of Unicode code points, as produced by the operating system text input system. 
		Unlike key input, text input obeys keyboard layouts and modifier keys and supports composing characters using dead keys. 
		Once received, you can encode the code points into UTF-8 or any other encoding you prefer.
		Because an unsigned int is 32 bits long on all platforms supported by GLFW, you can treat the code point argument as native endian UTF-32.
		If you wish to offer regular text input, set a character callback. */
	};

	// ---------------------
	// --- Cursor Events ---
	// ---------------------

	struct EventCursorPosition : Event 
	{
		EventCursorPosition(vec2 position_in = { 0.f , 0.f })
			: Event(EventType::CursorPosition), position(position_in)
		{}
		vec2 position;
	};
	struct EventCursorEntry : Event 
	{
		EventCursorEntry(bool entered_in)
			: Event(EventType::CursorEntry), entered(entered_in)
		{}
		bool entered;
	};

	// --------------------
	// --- Mouse Events ---
	// --------------------
	
	struct EventMouseScroll : Event {
		EventMouseScroll(const vec2& offset_in = { 0.f, 0.f })
			: Event(EventType::MouseScroll), offset(offset_in)
		{}
		inline static EventType GetType() { return EventType::MouseScroll; }
		vec2 offset;
	};
	struct EventMouseButton : Event {
		EventMouseButton(Mouse::Button button, Mouse::Action action, Keyboard::Modifier modifier = Keyboard::Modifier())
			: Event(EventType::MouseButton), button(button), action(action), modifier(modifier)
		{}
		Mouse::Button button;
		Mouse::Action action;
		Keyboard::Modifier modifier;
	};
	

	// ----------------------
	// --- Get Event Type ---
	// ----------------------

	template <typename T> constexpr static EventType GetEventType()
	{ return EventType::None; }
	#define DEF_GET_EVENT_TYPE(x) template<> inline constexpr static EventType GetEventType<Event ## x>() { return EventType:: ## x; }
	DEF_GET_EVENT_TYPE(WindowSize)
	DEF_GET_EVENT_TYPE(WindowPosition)
	DEF_GET_EVENT_TYPE(WindowFocus)
	DEF_GET_EVENT_TYPE(CursorPosition)
	DEF_GET_EVENT_TYPE(CursorEntry)
	DEF_GET_EVENT_TYPE(MouseButton)
	DEF_GET_EVENT_TYPE(MouseScroll)
	DEF_GET_EVENT_TYPE(KeyboardKey)
	DEF_GET_EVENT_TYPE(KeyboardText)

}
