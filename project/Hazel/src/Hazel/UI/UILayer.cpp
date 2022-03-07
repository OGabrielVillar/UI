#include "pch.h"
#include "UILayer.h"

#include "Structure/Components.h"
#include "UI/Viewport.h"

namespace Hazel {

	UILayer::UILayer(const Ref<entt::registry>& registry, entt::entity id)
		: m_ID(id),
		m_Registry(registry)
	{
		auto& cc = m_Registry->get<CommandCardComponent>(m_ID);
		
		cc.AddCommand(BIND_FN(UILayer::OnCursorMovement));

		cc.AddCommand(BIND_FN(UILayer::OnClick));
		cc.AddTrigger({Mouse::Button::Left, Mouse::Action::Press});

		cc.AddCommand(BIND_FN(UILayer::OnClickRelease));
		cc.AddTrigger({Mouse::Button::Left, Mouse::Action::Release});
	}

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

	Entity UILayer::NewSpace(const std::string& name)
	{
		return NewElement(name); 
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

	void UILayer::SetEdgeSnap(EdgeSnap snap)
	{
		m_Registry->get<LayoutComponent>(m_History[m_HistoryIndex]).SetEdgeSnap(snap);
	}

	void UILayer::SetWindowHandlePosition(Window& window)
	{
		m_Registry->emplace<WindowHandleComponent>(m_History[m_HistoryIndex], window);
	}

	MaterialComponent& UILayer::GetMaterial()
	{
		return m_Registry->get<MaterialComponent>(m_History[m_HistoryIndex]);
	}

	bool UILayer::OnClick()
	{
		auto& hierarchy = m_Registry->get<HierarchyComponent>(m_ID);

		return hierarchy.TopToBottomBool([this](Entity entity)
		{
			if (entity.HaveComponent<LayoutComponent>()) {
				auto& layout = entity.GetComponent<LayoutComponent>();

				bool hitTest = HitTest((vec2)m_CursorPosition, layout.GetRect());
				if ( hitTest ) {
					// Print names.
					if (entity.HaveComponent<InformationComponent>()) {
						auto& info = entity.GetComponent<InformationComponent>();
						std::cout << info.GetName() << std::endl;
					}
					// Drag window.
					if (entity.HaveComponent<WindowHandleComponent>()) {
						entity.GetComponent<WindowHandleComponent>().OnLeftPress((int)m_CursorPosition.x,(int)m_CursorPosition.y);
						m_IsDragging = true;
						m_DraggingID = entity.Raw();
					}
					return true;
				}
			}
			return false;
		});
	}

	bool UILayer::OnClickRelease()
	{
		if (m_IsDragging) {
			if (m_Registry->any_of<WindowHandleComponent>(m_DraggingID))
				m_Registry->get<WindowHandleComponent>(m_DraggingID).OnLeftRelease((int)m_CursorPosition.x, (int)m_CursorPosition.y);
			m_IsDragging = false;
		}

		return false;
	}

	bool UILayer::OnRightClick()
	{
		return false;
	}

	bool UILayer::OnDrag()
	{
		if (m_Registry->any_of<WindowHandleComponent>(m_DraggingID)) 
			m_Registry->get<WindowHandleComponent>(m_DraggingID).OnDrag((int)m_CursorPosition.x, (int)m_CursorPosition.y);
		
		return false;
	}

	bool UILayer::OnCursorMovement(const EventCursorPosition* event)
	{ 
		m_CursorPosition = event->position; 
		if (m_IsDragging)
			return OnDrag();
		return false; 
	}

	void UILayer::Close()
	{
		if(m_HistoryIndex > 0) {
			m_HistoryIndex--;
			m_WorkingEntity = m_History[m_HistoryIndex];
		}
	}

	HierarchyComponent& UILayer::GetHierarchy()
	{ 
		return m_Registry->get<HierarchyComponent>(m_ID); 
	}

}
