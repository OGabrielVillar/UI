#pragma once

#include <functional>
#include "Core/Flags.h"

namespace Hazel {

#define BIND_FN(x) [&](){ return x; }

	struct Function {
	public:
		Function() = default;
		Function(const std::function<bool()>& func_in)
			: m_function(func_in)
		{}
		template<class T>
		void BindFunction(T&& a) {
			m_function = std::move(a);
		}
		template <
			typename... Args,
			typename T,
			typename = typename std::enable_if<std::is_invocable_v<T, Args ...>, T>::type
		> // Must be a Function, Lambda or Functor.
			void SetFunctionWithArgs(T&& a) {
			m_function = std::function<bool(Args ...)>(a);
		}
		bool operator()() const {
			return m_function();
		}
		operator bool() const {
			return m_function.operator bool();
		}
	private:
		std::function<bool()> m_function;
	};

}
