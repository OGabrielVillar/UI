#pragma once

#include "Core/UUID.h"



namespace Hazel::Component {

	struct Information 
	{
		Information(const std::string& name, UUID::Type type = UUID::Type::Asset);
		std::string name;
		UUID uuid;
	};

}
