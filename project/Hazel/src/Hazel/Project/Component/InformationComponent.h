#pragma once

#include "Core/UUID.h"

#include "Component.h"

namespace Hazel {

	struct InformationComponent
	{
	public:
		InformationComponent(const std::string& name, UUID::Type type = UUID::Type::Asset);

	private:
		std::string name;
		UUID uuid;

	};

}
