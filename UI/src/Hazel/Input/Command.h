#pragma once

#include <string>

#include "InputSignal.h"
#include "Event.h"
#include "Core/Flags.h"

namespace Hazel {

	struct CommandCategory {

	};

	//[Command Flags]
	enum class CommandFlags : uint8_t {
		Remappable = BIT8(0),
		ShowOnRemappingTab = BIT8(1),
		ShowOnBottonInfoBar = BIT8(2),
	};

	//[Command]
	class Command {
	public: // Using
		using Flags = Flags<CommandFlags>;

	public: // Functions
		Command(const char* name_in = "unnamed")
			: m_name(name_in)
		{}
		bool Handle(const InputSignal& signal_in) {
			if (signal_in == m_inputSignal)
				return m_function();
			return false;
		}
		Flags& GetFlags() {
			return m_flags;
		}
		bool operator()() {
			return m_function();
		}
		template <
			typename T,
			typename = typename std::enable_if<std::is_invocable_v<T>, T>::type
		> // Must be a Function, Lambda or Functor.
		void SetFunction(T&& a) {
			m_function.BindFunction(std::move(a));
		}
		template <
			typename... Args,
			typename T,
			typename = typename std::enable_if<std::is_invocable_v<T, Args ...>, T>::type
		> // Must be a Function, Lambda or Functor.
			void SetFunctionWithArgs(T&& a) {
			m_function.SetFunctionWithArgs<Args ...>(std::move(a));
		}
		void Rename(const char* name_in) { m_name = name_in; }
		void SetInputSignal(const InputSignal& signal_in) { m_inputSignal = signal_in; }
		void SetCategory(const CommandCategory& category_in) { m_category = category_in; }

		const InputSignal& GetInputSignal() const { return m_inputSignal; }
	private: // Members
		InputSignal m_inputSignal;
		std::string m_name;
		CommandCategory m_category;
		Function m_function;
		Flags m_flags;

	};

}
