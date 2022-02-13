#include "pch.h"
#include "Entity.h"

namespace Hazel {

	Camera::Camera(const vec2& aspectRatio)
		: m_CameraComponent(aspectRatio, m_TransformComponent.GetMat4())
	{
	}

}
