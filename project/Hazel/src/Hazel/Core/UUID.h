#pragma once

namespace Hazel {

	using hz_uuid_t = uint32_t;
	using hz_uuid_user_t = uint16_t;


	class UUID 
	{
	private:
		static hz_uuid_user_t s_UserID;

	public:
		enum class Type : uint8_t 
		{
			None = 0,
			Asset,
			Entity,
			SpawnedEntity,
		};
		
	private:
		class Data 
		{
		public:
			Data(hz_uuid_t id, hz_uuid_user_t userId, uint8_t type);
			Data(const Data&) = default;
		private:
			hz_uuid_t m_ID;
			hz_uuid_user_t m_UserID;
			uint8_t m_Type;
			uint8_t __h = 0; // To complete 8 bytes
		};
		
	private:
		class Registry 
		{
		public:
			Registry(Type type)
				: m_Type((uint8_t)type)
			{}
			
			UUID GenerateUUID() { 
				return UUID({m_CurrentID++, s_UserID, m_Type}); 
			}

		private:
			hz_uuid_t m_CurrentID = 0;
			uint8_t  m_Type;
		};

		static Registry s_AssetsRegistry;
		static Registry s_EntitiesRegistry;
		static Registry s_SpawnsRegistry;
		
	private:
		UUID(const Data& data);

	public:
		static UUID NewAsset();
		static UUID NewEntity();
		static UUID NewSpawn();

		UUID() {}
		UUID(const UUID&) = default;

	public:
		operator uint64_t() const { return m_id; }
		
	public:
		union 
		{
			uint64_t m_id = 0;
			Data m_data;
		};
	};

}
