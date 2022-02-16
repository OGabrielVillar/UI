#include "pch.h"
#include "UUID.h"

namespace Hazel {
	using namespace Math;
	
	Random Random::inst; // TODO: Random instance initialization in UUID cpp file is wrong.
	
	hz_uuid_user_t UUID::s_UserID((hz_uuid_user_t)Random::uInt());
	
	UUID::Registry UUID::s_AssetsRegistry(UUID::Type::Asset);
	UUID::Registry UUID::s_EntitiesRegistry(UUID::Type::Entity);
	UUID::Registry UUID::s_SpawnsRegistry(UUID::Type::SpawnedEntity);

	UUID::Data::Data(hz_uuid_t id, hz_uuid_user_t userId, uint8_t type)
	  : m_ID(id),
		m_UserID(userId),
		m_Type(type)
	{}

	UUID::UUID(const UUID::Data& data)
	  : m_data(data)
	{}

	UUID UUID::NewAsset()
	{
		return s_AssetsRegistry.GenerateUUID();
	}

	UUID UUID::NewEntity()
	{
		return s_EntitiesRegistry.GenerateUUID();
	}

	UUID UUID::NewSpawn()
	{
		return s_SpawnsRegistry.GenerateUUID();
	}

}
