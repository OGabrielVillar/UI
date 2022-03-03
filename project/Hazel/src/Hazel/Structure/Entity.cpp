#include "pch.h"
#include "Entity.h"

#include "Components.h"

namespace Hazel {

	// --------------
	// --- Entity ---
	// --------------

	Entity::Entity()
	{}

	Entity::Entity(Ref<entt::registry>& registry)
	  : m_ID(registry->create()),
		m_Registry(registry)
	{}

	Entity::Entity(Ref<entt::registry>&registry, entt::entity id)
	  : m_ID(id),
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

	// --------------------
	// --- CameraEntity ---
	// --------------------

	CameraEntity::CameraEntity(Ref<entt::registry>& registry, const vec2& aspectRatio)
	  : Entity(registry, "Camera")
	{
		auto transform = AddComponent<TransformComponent>();
		AddComponent<CameraComponent>(aspectRatio, transform->GetMat4());
	}

	void CameraEntity::SetAspectRatio(const vec2& aspectRatio)
	{ 
		GetCamera().SetAspectRatio(aspectRatio); 
	}

	const mat4& CameraEntity::GetViewProjectionMatrix()
	{ 
		return GetCamera().GetViewProjectionMatrix(); 
	}

	TransformComponent& CameraEntity::GetTransform()
	{
		 return m_Registry->get<TransformComponent>(m_ID);
	}

	CameraComponent& CameraEntity::GetCamera()
	{
		 return m_Registry->get<CameraComponent>(m_ID);
	}

}
