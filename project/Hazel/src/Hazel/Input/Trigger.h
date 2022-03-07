#pragma once

#include "Event.h"

namespace Hazel {

	// ---------------
	// --- Trigger ---
	// ---------------
	enum class TriggerFlag : uint8_t {
		AnyAction = BIT(1),
		AnyModifier = BIT(2),
	};

	class Trigger {
	public:
		using Flag = TriggerFlag;
		using Flags = Flags<Flag>;
	public:
		Trigger(KeyCode code, KeyAction action = KeyAction::Release, KeyModifier modifier = (KeyModifier)0) 
		  : m_KeyCode(code), m_KeyAction(action), m_KeyModifier(modifier), m_Type(EventType::KeyboardKey)
		{}
		Trigger(MouseCode code, MouseAction action = MouseAction::Release, KeyModifier modifier = (KeyModifier)0) 
		  : m_MouseCode(code), m_MouseAction(action), m_KeyModifier(modifier), m_Type(EventType::MouseButton)
		{}

		EventType GetType() const { return m_Type; }

#define CASE(EVENT_TYPE) case EventType:: ## EVENT_TYPE:
		bool Match(const Event& event)
		{
			bool matches = true;

			if (event.type != m_Type) return false;

			const EventKeyboardKey& KeyboardKey = *((EventKeyboardKey*)&event);
			const EventMouseButton& MouseButton = *((EventMouseButton*)&event);

			switch (event.type) {
			CASE(KeyboardKey)
				if (KeyboardKey.key != m_KeyCode) {
					matches = false;
					break;
				}
				if (m_Flags.NotContains(Flag::AnyAction))
					if (KeyboardKey.action != m_KeyAction) {
						matches = false;
						break;
					}
				if (m_Flags.NotContains(Flag::AnyModifier))
					if (KeyboardKey.modifier != m_KeyModifier) {
						matches = false;
						break;
					}
				break;
			CASE(MouseButton)
				if (MouseButton.button != m_MouseCode) {
					matches = false;
					break;
				}
				if (m_Flags.NotContains(Flag::AnyAction))
					if (MouseButton.action != m_MouseAction) {
						matches = false;
						break;
					}
				if (m_Flags.NotContains(Flag::AnyModifier))
					if (MouseButton.modifier != m_KeyModifier) {
						matches = false;
						break;
					}
				break;
			default:
				matches = false;
				break;
			}
			return matches;

		}
#undef Case

	private:
		union {
			KeyCode m_KeyCode;
			MouseCode m_MouseCode; 
		};
		union {
			KeyAction m_KeyAction;
			MouseAction m_MouseAction; 
		};
		KeyModifier m_KeyModifier;
		EventType m_Type = EventType::None;
		Flags m_Flags;
	};

}
