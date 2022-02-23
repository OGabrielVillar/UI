#include "pch.h"
#include "Project.h"

#include "Component/InformationComponent.h"
#include "Component/CommandCardComponent.h"
#include "UI/UILayer.h"

#include "Graphics/Renderer/Renderer.h"

namespace Hazel {

	void Project::Render()
	{
		PROFILE("Project::Render()");
		auto view = m_Registry.view<UILayerComponent>();
		for (auto ent : view)
		{
			auto& ui = view.get<UILayerComponent>(ent);
			Renderer::DrawUI(ui);
		}
	}

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

	Entity Project::CreateUILayer(const Ref<Canvas>& canvas, const std::string& name)
	{
		auto ent = Entity(m_Registry);
		ent.AddComponent<InformationComponent>(name);
		ent.AddComponent<UILayerComponent>(m_Registry, canvas);
		return ent;
	}

}
