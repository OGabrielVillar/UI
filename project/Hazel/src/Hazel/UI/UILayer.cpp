#include "pch.h"
#include "UILayer.h"

#include "Structure/Components.h"
#include "UI/Viewport.h"

namespace Hazel {

	Entity UILayer::NewElement(const std::string& name)
	{
		Entity element(m_Registry, name);

		auto* elementLayout= element.AddComponent<LayoutComponent>();

		m_WorkingEntity = element.Raw();

		m_HistoryIndex++;
		m_History[m_HistoryIndex] = element.Raw();

		if (m_HistoryIndex > 1) {
			auto* elementHierarchy = element.AddComponent<HierarchyComponent>(
				m_Registry,
				m_History[m_HistoryIndex],
				m_Registry->get<HierarchyComponent>(m_History[m_HistoryIndex -1]));
			elementLayout->SetHierarchy(*elementHierarchy );
		} else {
			auto* elementHierarchy = element.AddComponent<HierarchyComponent>(
				m_Registry,
				m_History[m_HistoryIndex],
				m_Registry->get<HierarchyComponent>(m_ID));
			elementLayout->SetHierarchy(*elementHierarchy );
		}

		return element;
	}

	Entity UILayer::NewFrame(const std::string& name)
	{
		auto element = NewElement(name);

		auto elementViewport = element.AddComponent<MaterialComponent>();

		return element;
	}

	Entity UILayer::NewViewport(const std::string& name)
	{
		auto element = NewElement(name);

		auto elementViewport = element.AddComponent<ViewportComponent>();

		return element;
	}

	void UILayer::SetSize(const vec2& size)
	{
		m_Registry->get<LayoutComponent>(m_History[m_HistoryIndex]).SetSize(size);
	}

	void UILayer::SetPosition(const vec2& position)
	{
		m_Registry->get<LayoutComponent>(m_History[m_HistoryIndex]).SetPosition(position);
	}

	void UILayer::SetAnchor(Anchor anchor)
	{
		m_Registry->get<LayoutComponent>(m_History[m_HistoryIndex]).SetAnchor(anchor);
	}

	void UILayer::SetSnap(Snap snap)
	{
		m_Registry->get<LayoutComponent>(m_History[m_HistoryIndex]).SetSnap(snap);
	}

	MaterialComponent& UILayer::GetMaterial()
	{
		return m_Registry->get<MaterialComponent>(m_History[m_HistoryIndex]);
	}

	void UILayer::Close()
	{
		if(m_HistoryIndex > 0) {
			m_HistoryIndex--;
			m_WorkingEntity = m_History[m_HistoryIndex];
		}
	}

}
