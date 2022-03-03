#include "pch.h"
#include "Components.h"

#include "Entity.h"

namespace Hazel {

	CameraEntity::CameraEntity(Ref<entt::registry>& registry, const vec2& aspectRatio)
	  : Entity(registry, "Camera")
	{
		auto transform = AddComponent<TransformComponent>();
		AddComponent<CameraComponent>(aspectRatio, transform->GetMat4());
	}

	// --------------
	// --- Entity ---
	// --------------

	Entity::Entity()
	{}

	Entity::Entity(Ref<entt::registry>& registry)
		: m_ID(registry->create()),
		m_Registry(registry)
	{}

	Entity::Entity(Ref<entt::registry>& registry, const std::string& name)
	  : m_ID(registry->create()),
		m_Registry(registry)
	{
		m_Registry->emplace<InformationComponent>(m_ID, name);		
	}

	Entity::Entity(const Entity& other)
	  : m_ID(other.m_ID),
		m_Registry(other.m_Registry)
	{}

	Entity& Entity::operator=(const Entity & other)
	{
		m_ID = other.m_ID;
		m_Registry = other.m_Registry;
		return *this;
	}

}
