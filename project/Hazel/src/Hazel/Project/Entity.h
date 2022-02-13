#pragma once

#include "Components/Transform.h"
#include "Components/Camera.h"

namespace Hazel {

	class Entity {
	private:
	};

	class Camera : Entity 
	{
	public:
		Camera(const vec2& aspectRatio);
		
		inline void SetAspectRatio(const vec2& aspectRatio){ m_CameraComponent.SetAspectRatio(aspectRatio); }
		inline const mat4& GetViewProjectionMatrix() { return m_CameraComponent.GetViewProjectionMatrix(); }

		inline TransformComponent& GetTransform() { return m_TransformComponent; }
		//inline CameraComponent& GetCamera() { return m_CameraComponent; }
	private:
		TransformComponent m_TransformComponent;
		CameraComponent m_CameraComponent;
	};

}
