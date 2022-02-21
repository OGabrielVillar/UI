#include "pch.h"
#include "Project.h"

#include "Component/InformationComponent.h"
#include "Component/CommandCardComponent.h"

namespace Hazel {

	void Project::Update()
	{

	}

	bool Project::OnEvent(const Event& event)
	{
		auto view = m_Registry.view<CommandCardComponent>();
		for (auto entity : view) {
			CommandCardComponent& card = view.get<CommandCardComponent>(entity);
			if (card.OnEvent(event)) return true;
		}
		return false;
	}

	Entity Project::CreateEntity(const std::string& name)
	{
		auto ent = Entity(m_Registry);
		ent.AddComponent<InformationComponent>(name);
		return ent;
	}

	Ref<CameraEntity> Project::CreateCamera(const vec2& aspectRatio, const std::string& name)
	{
		auto cmr = CreateReference<CameraEntity>(m_Registry, aspectRatio);
		cmr->AddComponent<InformationComponent>(name);
		return cmr;
	}

}
