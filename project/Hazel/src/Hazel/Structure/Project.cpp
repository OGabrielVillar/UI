#include "pch.h"
#include "Project.h"

#include "Components.h"
#include "UI/UILayer.h"

#include "Graphics/Renderer.h"

namespace Hazel {

	void Project::Render()
	{
		PROFILE("Project::Render()");
		auto view = m_Registry->view<UILayerComponent>();
		for (auto ent : view)
		{
			auto& ui = view.get<UILayerComponent>(ent);
			Renderer::DrawUI(ui);
		}
	}

	bool Project::OnEvent(const Event& event)
	{
		auto view = m_Registry->view<CommandCardComponent>();
		for (auto entity : view) {
			CommandCardComponent& card = view.get<CommandCardComponent>(entity);
			if (card.OnEvent(event)) return true;
		}
		return false;
	}

	Entity Project::CreateEntity(const std::string& name)
	{
		auto ent = Entity(m_Registry, name);
		return ent;
	}

	Ref<CameraEntity> Project::CreateCamera(const vec2& aspectRatio, const std::string& name)
	{
		auto cmr = CreateReference<CameraEntity>(m_Registry, aspectRatio);
		return cmr;
	}

	Entity Project::CreateUILayer(const std::string& name)
	{
		auto ent = Entity(m_Registry, name);
		ent.AddComponent<UILayerComponent>(m_Registry, ent.Raw());
		auto hierarchy = ent.AddComponent<HierarchyComponent>(m_Registry, ent.Raw());
		ent.AddComponent<LayoutComponent>()->SetHierarchy(*hierarchy);
		return ent;
	}

	Entity Project::CreateScene(const Ref<Canvas>& canvas, const std::string& name)
	{
		auto ent = Entity(m_Registry, name);
		auto scene = ent.AddComponent<SceneComponent>(canvas);
		return ent;
	}

}
