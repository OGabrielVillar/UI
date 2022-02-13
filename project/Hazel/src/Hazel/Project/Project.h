#pragma once

#include "Input/Event.h"
#include "Layer.h"

namespace Hazel {

	struct ProjectInformation
	{
		std::string name;
	};

	class Project 
	{
	public:
		void Run(const Event& event);
	private:
		ProjectInformation m_Information;
		Ref<Layer> m_Layer;
	};

}
