#pragma once

#include "pch.h"
#include "Core/Containers/Stack.h"

namespace Hazel
{
	using Containers::Stack;

	class RunCycle
	{
		RunCycle(const std::initializer_list<std::function<void(void)>>& functions);
		void Run();
	 private:
		std::vector<std::function<void(void)>> m_Functions;
	};

}
