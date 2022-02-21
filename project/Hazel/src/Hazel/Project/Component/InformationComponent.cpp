#include "pch.h"
#include "InformationComponent.h"

namespace Hazel {

	//Requires<> Information::Requisite;
	
	InformationComponent::InformationComponent(const std::string& name, UUID::Type type)
		: name(name)
	{
		switch (type) {
		case UUID::Type::None:
			HZ_ASSERT(false, "InformationComponent: Invalid type!");
			break;
		case UUID::Type::Asset:
			uuid = UUID::NewAsset(); 
			break;
		case UUID::Type::Entity:
			uuid = UUID::NewEntity();
			break;
		case UUID::Type::SpawnedEntity:
			uuid = UUID::NewSpawn();
			break;
		default:
			HZ_ASSERT(false, "InformationComponent: Invalid type!");
			break;
		}
	}

}
