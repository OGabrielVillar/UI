#pragma once

#include "Trigger.h"

namespace Hazel {

	// ---------------
	// --- Command ---
	// ---------------
	class Command {
	public:
		//Command(const Command&) = delete;
		//Command& operator=(const Command&) = delete;

		template<typename T, typename Arg>
		constexpr Command(T* object, bool(T::*function)(const Arg*))
		  : m_Arg(GetEventType<Arg>()), 
			m_Function(std::bind((bool(T::*)(const Event*))function, object, std::placeholders::_1))
		{
			static_assert(std::is_base_of_v<Event, Arg>, "Function argument is not a type derived from event!");
		}

		template<typename Arg>
		constexpr Command(bool(*function)(const Arg*))
		  : m_Arg(GetEventType<Arg>()), 
			m_Function(function)
		{
			static_assert(std::is_base_of_v<Event, Arg>, "Function argument is not a type derived from event!");
		}

		template<typename T>
		constexpr Command(T* object, bool(T::*function)())
		  : m_Arg(EventType::None),
			m_Function( [object, function](const Event*){ 
				return ((*object).*function)(); 
			})
		{}

		void AddTrigger(const Trigger& trigger)
		{
			if (m_Arg == EventType::None)
				m_Triggers.push_back(trigger);
			else 
				HZ_ASSERT(false, "Command::AddTrigger: Cannot add trigger in a command with argument type defined!");
		}

		bool Handle(const Event& event)
		{
			if (m_Triggers.empty()) {
				if (event.type == m_Arg)
					return m_Function(&event);
			} else {
				for (auto& trigger : m_Triggers)
					if (trigger.Match(event))
						return m_Function(&event);
			}
			return false;
		}

	private:
		const EventType m_Arg;
		std::function<bool(const Event*)> m_Function;
		std::vector<Trigger> m_Triggers;
	};

	#define BIND_FN(Fn) this, &Fn

}
