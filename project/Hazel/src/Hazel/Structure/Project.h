#pragma once

#include "Input/Event.h"
#include "Canvas.h"

#include "Entity.h"

namespace Hazel {

	struct ProjectInformation
	{
		std::string name = "Project";
	};

	class Project 
	{
	public:
		void Render();
		void Update();
		bool OnEvent(const Event& event);

		Entity CreateEntity(const std::string& name = "Entity");
		Ref<CameraEntity> CreateCamera(const vec2& aspectRatio, const std::string& name = "Camera");
		Entity CreateUILayer(const std::string& name = "UILayer");
		Entity CreateScene(const Ref<Canvas>& canvas, const std::string& name = "Scene");

	private:
		ProjectInformation m_Information;
		Ref<entt::registry> m_Registry = CreateReference<entt::registry>();
	};

}
