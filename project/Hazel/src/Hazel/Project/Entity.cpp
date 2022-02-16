#include "pch.h"
#include "Entity.h"

namespace Hazel {

	Camera::Camera(entt::registry& registry, const vec2& aspectRatio)
	  : Entity(registry),
		m_CameraComponent(aspectRatio, m_TransformComponent.GetMat4())
	{
	}

}
