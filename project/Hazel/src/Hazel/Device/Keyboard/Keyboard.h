#pragma once

#include "KeyboardCodes.h"

#include "Input/Event.h"

namespace Hazel 
{

	class Keyboard {
	public:
		using Key = KeyCode;
		using Modifier = KeyModifier;
		using Action = KeyAction;
		using Modifiers = Flags<KeyModifier>;
	};

	struct EventKeyboardKey : Event {
		EventKeyboardKey(Keyboard::Key key, Keyboard::Action action, Keyboard::Modifier modifier = Keyboard::Modifier())
			: Event(EventType::KeyboardKey), key(key), action(action), modifier(modifier)
		{}
		inline bool operator==(const EventKeyboardKey& other) const { return key == other.key && action == other.action && modifier == other.modifier; }
		inline static EventType GetType() { return EventType::KeyboardKey; }

		Keyboard::Key key;
		Keyboard::Modifier modifier;
		Keyboard::Action action;
	};

	struct EventKeyboardText : Event {
		EventKeyboardText(uint32_t character)
			: Event(EventType::KeyboardText), character(character)
		{}
		inline bool operator==(const EventKeyboardText& other) const { return true; }
		inline static EventType GetType() { return EventType::KeyboardText; }
		uint32_t character;
		/* LFW supports text input in the form of a stream of Unicode code points, as produced by the operating system text input system. 
		Unlike key input, text input obeys keyboard layouts and modifier keys and supports composing characters using dead keys. 
		Once received, you can encode the code points into UTF-8 or any other encoding you prefer.
		Because an unsigned int is 32 bits long on all platforms supported by GLFW, you can treat the code point argument as native endian UTF-32.
		If you wish to offer regular text input, set a character callback. */
	};

}
