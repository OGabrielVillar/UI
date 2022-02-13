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
		inline Camera& GetCamera() { return *m_Camera; }

	private:
		Ref<Layer> m_Layer;
		Ref<Camera> m_Camera = CreateReference<Camera>(vec2(1.f,1.f));
	};

}
