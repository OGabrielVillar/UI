#pragma once

#include "Input/Command.h"

namespace Hazel {

	struct CommandCard {
	 public:
		inline bool OnEvent(const Event& event) 
		{ 
			for (auto& command : m_Commands)
				if (command.Handle(event)) 
					return true;			
			return false; 
		}
		template<typename ... Args>
		inline Command& AddCommand(Args ... args)
		{
			m_Commands.emplace_back(std::forward<Args>(args)...);
			return m_Commands.back();
		}
		inline void AddTrigger(const Trigger& trigger)
		{
			m_Commands.back().AddTrigger(trigger);
		}
	 private:
		std::vector<Command> m_Commands;
	};

}
