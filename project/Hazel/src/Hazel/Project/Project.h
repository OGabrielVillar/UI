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
		void Update();
		bool OnEvent(const Event& event);

		Entity CreateEntity(const std::string& name = "Entity");
		Ref<CameraEntity> CreateCamera(const vec2& aspectRatio, const std::string& name = "Camera");

	private:
		ProjectInformation m_Information;
		entt::registry m_Registry;
	};

}
