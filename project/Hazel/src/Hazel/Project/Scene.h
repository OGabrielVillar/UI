#pragma once

#include "Entity.h"
#include "Canvas.h"

namespace Hazel 
{

	enum class SceneType {
		UseCanvasResolution,
		UseCamera
	};

	class Scene
	{
	public:
		Scene(const Ref<Canvas>& Canvas)
			: m_Canvas(Canvas)
		{}

		inline void SetCanvas(const Ref<Canvas>& Canvas) { m_Canvas = Canvas; }
		inline void SetCamera(const Ref<CameraEntity>& camera) { m_Camera = camera; }

		inline Canvas& GetCanvas() { return *m_Canvas; }
		//inline Camera& GetCamera() { return *m_Camera; }
		inline const glm::mat4& GetCameraMatrix() 
		{ 
			if (m_Camera == nullptr) {
				HZ_ASSERT(false, "Scene::GetCanvas: Doesn't handle the situation in case of not having a camera!")
				return glm::mat4(1.f);
			} else
				return m_Camera->GetViewProjectionMatrix(); 
		}

	private:
		Ref<Canvas> m_Canvas = nullptr;
		Ref<CameraEntity> m_Camera = nullptr;
		SceneType m_Type;
	};

}
