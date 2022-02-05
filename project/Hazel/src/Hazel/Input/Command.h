#pragma once

#include "Device/Keyboard/Keyboard.h"
#include "Device/Mouse/Mouse.h"

namespace Hazel {
	
	using CommandCategory = string;
	
	//[Command Flags]
	enum class CommandFlag : uint8_t {
		Remappable			= BIT(0),
		ShowOnRemappingTab	= BIT(1),
		ShowOnBottonInfoBar = BIT(2),
	};

	//[Command]
	class Command {
	 public:
		using Flag = CommandFlag;
		using Flags = Flags<CommandFlag>;

	 public:
		template<typename T,
				 typename = typename std::enable_if<std::derived_from<T, Event>>::type>
		Command(const string& name, const T& event, Flags flags = Flags())
			: m_Name(name), m_Event(std::make_unique<T>(event))
		{}

		void Rename(const char* name) { m_Name = name; }
		template<typename T,
				 typename = typename std::enable_if<std::derived_from<T, Event>>::type>
		inline void SetFunction(std::function<bool(const T*)> function) {
			m_Function = *((std::function<bool(void*)>*)&function);
		}
		template<typename T,
				 typename = typename std::enable_if<std::derived_from<T, Event>>::type>
		void SetInputEvent(const T& event) { m_Event.reset(std::make_unique<T>(event)); }
		void SetCategory(const CommandCategory& category) { m_Category = category; }

		inline bool Handle(const Event& event) {
			#define CASE(TYPE) case EventType::TYPE: return Handle<TYPE ## Event>(event)
			if (m_Event->type == event.type)
				switch (event.type)
				{
					//CASE(WindowSize);
					//CASE(WindowFocus);
					//CASE(WindowPosition);
					CASE(CursorPosition);
					CASE(CursorEntry);
					CASE(MouseButton);
					CASE(MouseScroll);
					CASE(KeyboardKey);
					CASE(KeyboardText);
				};
			#undef CASE
			return false;
		}
	 private:
		template<typename T,
				 typename = typename std::enable_if<std::derived_from<T, Event>>::type>
		inline bool Handle(const Event& event) {
			const T& e = static_cast<const T&>(event);
			if (static_cast<const T&>(*m_Event) == e)
				return m_Function((void*)&e);
			return false;
		}

	 private:
		              Scope<Event> m_Event;
		std::function<bool(void*)> m_Function;
		                    string m_Name;
		           CommandCategory m_Category;
		                     Flags m_Flags;

	};


}
