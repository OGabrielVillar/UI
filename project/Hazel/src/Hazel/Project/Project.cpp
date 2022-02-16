#include "pch.h"
#include "Project.h"

#include "Component/InformationComponent.h"

namespace Hazel {
    Entity Project::CreateEntity(const std::string& name)
    {
		auto ent = Entity(m_Registry);
		ent.AddComponent<Component::Information>(name);
		return ent;
    }
	Ref<Camera> Project::CreateCamera(const vec2& aspectRatio, const std::string& name)
	{
		auto cmr = CreateReference<Camera>(m_Registry, aspectRatio);
		cmr->AddComponent<Component::Information>(name);
		return cmr;
	}
}
