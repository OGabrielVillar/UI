#pragma once

#include "Input/Event.h"
#include "Layer.h"

#include "Entity.h"

namespace Hazel {

	struct ProjectInformation
	{
		std::string name = "Project";
	};

	class Project 
	{
	public:
		Entity CreateEntity(const std::string& name = "Entity");
		Ref<Camera> CreateCamera(const vec2& aspectRatio, const std::string& name = "Camera");
		void Run(const Event& event);
	private:
		ProjectInformation m_Information;
		entt::registry m_Registry;
	};

}
