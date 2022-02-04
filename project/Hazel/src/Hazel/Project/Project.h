#pragma once

namespace Hazel 
{

	class Project {
	public:
		void Run(InputPack inputs);
	private:
		Entities m_Entities;
		RunCycle m_RunCycle;
	};

}
