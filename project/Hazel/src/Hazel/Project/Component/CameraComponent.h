#pragma once

#include "Project/Camera.h"

#include "Component.h"
#include "TransformComponent.h"
#include "InformationComponent.h"

namespace Hazel
{

	struct CameraComponent : public Camera2 {
	 public:
		CameraComponent(const vec2& aspectRatio, const Ref<const mat4> transform)
		  : Camera2(aspectRatio, transform)
		{}

		REQUIRES(TransformComponent);
	};

}
