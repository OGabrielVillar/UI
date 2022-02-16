#pragma once

#include "Entity.h"
#include "Layer.h"

namespace Hazel 
{

	class Scene
	{
	public:
		Scene(const Ref<Layer>& layer)
			: m_Layer(layer)
		{}

		inline void SetLayer(const Ref<Layer>& layer) { m_Layer = layer; }
		inline void SetCamera(const Ref<Camera>& camera) { m_Camera = camera; }

		inline Layer& GetLayer() { return *m_Layer; }
		//inline Camera& GetCamera() { return *m_Camera; }
		inline const glm::mat4& GetCameraMatrix() 
		{ 
			if (m_Camera == nullptr) {
				HZ_ASSERT(false, "Scene::GetLayer: Doesn't handle the situation in case of not having a camera!")
				return glm::mat4(1.f);
			} else
				return m_Camera->GetViewProjectionMatrix(); 
		}

	private:
		Ref<Layer> m_Layer = nullptr;
		Ref<Camera> m_Camera = nullptr;
	};

}
