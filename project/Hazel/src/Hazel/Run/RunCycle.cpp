#include "pch.h"
#include "RunCycle.h"

namespace Hazel 
{

	RunCycle::RunCycle(const std::initializer_list<std::function<void(void)>>& functions)
		: m_Functions(functions)
	{}

	void RunCycle::Run()
	{
		for (std::function<void(void)>& fn : m_Functions)
		{
			fn();
		}
	}

}
