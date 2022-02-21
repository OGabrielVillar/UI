#pragma once

#include <vector>
#include "Input/Command.h"

#include "Component.h"

namespace Hazel {

	struct CommandCardComponent {
	 public:
		inline bool OnEvent(const Event& event) 
		{ 
			for (auto& command : m_Commands)
				if (command->Handle(event)) 
					return true;			
			return false; 
		}
		inline Ref<Command> AddCommand()
		{
			m_Commands.push_back(CreateReference<Command>());
			return m_Commands.back();
		}
	 private:
		std::vector<Ref<Command>> m_Commands;
	};

}
