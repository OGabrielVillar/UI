#pragma once

#include "Command.h"
#include "InputSignal.h"

namespace Hazel {

	class CommandCollection {
	 public:
		bool AddCommand(const Command& command_in) {
			m_cmds.push_back(command_in);
			return true;
		}
		Command& AddCommand() {
			m_cmds.push_back(Command());
			return m_cmds.back();
		}
		bool RunInput(const InputSignal& code_in) {
			if ((int)code_in.action <= 2)
				int i = 0;
			for (Command& cmd : m_cmds) {
				if (cmd.Handle(code_in))
					return true;
			}
			return false;
		}
	 private:
		std::vector<Command> m_cmds;
	};

}