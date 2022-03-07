#pragma once

#include "Device/Keyboard/Keyboard.h"
#include "Device/Mouse/Mouse.h"
#include "Input/Cursor.h"

namespace Hazel {

#define BIND_FN(EVENT_TYPE, LAMBDA) std::function<bool(const EVENT_TYPE*)>(LAMBDA)
	


	//[Command Trigger]
	struct CommandTrigger {
	public:
		CommandTrigger() = default;
		CommandTrigger(const CommandTrigger& other) 
		{
			#define CASE(TYPE) case EventType::TYPE: m_Event = std::make_unique<Event ## TYPE>(*((Event ## TYPE*)&event)); break;
			Event& event = *other.m_Event;
			switch (event.type){
				CASE(WindowPosition);
				CASE(WindowSize);
				CASE(WindowFocus);
				CASE(CursorPosition);
				CASE(CursorEntry);
				CASE(MouseButton);
				CASE(MouseScroll);
				CASE(KeyboardKey);
				CASE(KeyboardText);
			}
			#undef CASE
		}

		template<typename T,
				 typename = typename std::enable_if<std::derived_from<T, Event>>::type>
		CommandTrigger(const T& event)
			: m_Event(std::make_unique<T>(event))
		{}

		template<typename T,
				 typename = typename std::enable_if<std::derived_from<T, Event>>::type>
		bool Evaluate(const T& event) const
		{
			if (event.type == m_Event->type)
				if (static_cast<const T&>(*m_Event) == event)
					return true;
			return false;
		}

	private:
		Scope<Event> m_Event;
	};


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
		Command() = default;
		Command(const std::function<bool()>& function) 
		{ 
			SetFunction(function); 
		}

		// Add Trigger
		template<typename EVENT,
				 typename = typename std::enable_if<std::derived_from<EVENT, Event>>::type>
		inline void AddTrigger(const EVENT& event)
		{
			if (m_Type == EVENT::GetType()) {
				m_Triggers.push_back(CommandTrigger(event));
			} else {
				HZ_ASSERT(false, "Command::AddTrigger: Command needs a function before adding a trigger!");
			}
		}
		
		// Handle Dispatcher
		inline bool Handle(const Event& event) 
		{
		#define CASE(TYPE) case EventType::TYPE: return Handle<Event ## TYPE>(static_cast<const Event ## TYPE ## &>(event))
			switch (event.type)
			{
				CASE(WindowPosition);
				CASE(WindowSize);
				CASE(WindowFocus);
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
		
		// Set Function with event argument;
		template<typename EVENT, typename F,
				 typename = typename std::enable_if<std::derived_from<EVENT, Event>>::type>
		inline void SetFunction(const F& function)
		{
			if (m_Function) {
				HZ_ASSERT(false, "Command::SetFunction<>: Command already have a function!")
			} else {
				m_Type = EVENT::GetType();
				*((std::function<bool(EVENT*)>*)&m_Function) = function;
			}
		}
		// Set Function with no arguments;
		inline void SetFunction(const std::function<bool()>& function)
		{
			if (m_Function) {
				HZ_ASSERT(false, "Command::SetFunction<>: Command already have a function!")
			} else {
				m_Type = TriggerFlag::Any;
				*((std::function<bool()>*)&m_Function) = function;
			}
		}

	 private:
		// Handle
		template<typename T,
				 typename = typename std::enable_if<std::derived_from<T, Event>>::type>
		inline bool Handle(const T& event) {
			for (const CommandTrigger& trigger : m_Triggers)
				if (m_Function && trigger.Evaluate(event))
					return m_Function((void*)&event);
			return false;
		}

	 private:
		TriggerType m_Type;
		std::vector<CommandTrigger> m_Triggers;
		std::function<bool(void*)> m_Function;
		Flags m_Flags;

	};
	template<typename T>
	Command addCommand(){}
}
