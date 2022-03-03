#pragma once

#include "Core/Data/UUID.h"

namespace Hazel {

	struct Information
	{
	public:
		Information(const std::string& name, UUID::Type type = UUID::Type::Asset);

	private:
		std::string name;
		UUID uuid;

	};

}
