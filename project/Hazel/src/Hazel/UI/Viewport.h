#pragma once

#include "Structure/Canvas.h"
#include "Structure/Entity.h"
#include "Structure/Scene.h"

namespace Hazel {

	class Viewport {
	public:
		Viewport() = default;

		void SetScene(Entity sceneEntity);

		inline SceneComponent& GetScene() { return m_SceneEntity.GetComponent<SceneComponent>(); }

	protected:
		Entity m_SceneEntity;
	};

}
