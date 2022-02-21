#include "pch.h"
#include "Entity.h"

//#include <entt/entt.hpp>


namespace Hazel {

	CameraEntity::CameraEntity(entt::registry& registry, const vec2& aspectRatio)
	  : Entity(registry)
	{
		auto transform = AddComponent<TransformComponent>();
		AddComponent<CameraComponent>(aspectRatio, transform->GetMat4());
	}

}
