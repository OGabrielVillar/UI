#pragma once

#include "Core/Data/UUID.h"

namespace Hazel {

	struct Information
	{
	public:
		Information(const std::string& name, UUID::Type type = UUID::Type::Asset);

		inline const std::string& GetName() { return name; }
		inline const UUID& GetUUID() { return uuid; }

	private:
		std::string name;
		UUID uuid;

	};

}
