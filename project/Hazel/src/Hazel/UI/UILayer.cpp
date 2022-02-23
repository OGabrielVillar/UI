#include "pch.h"
#include "UILayer.h"

#include "UI/Layout.h"

namespace Hazel {

	Entity UILayer::NewFrame(const vec2& position, const vec2& size)
	{
		Entity frame(m_Registry);
		frame.AddComponent<LayoutComponent>(position, size);

		m_Tree.push([this](entt::entity value){ return value == m_WorkingEntity; }, frame.Raw());

		m_WorkingEntity = frame.Raw();

		m_HistoryIndex++;
		m_History[m_HistoryIndex] = frame.Raw();

		return frame;
	}

	void UILayer::Close()
	{
		if(m_HistoryIndex > 0) {
			m_HistoryIndex--;
			m_WorkingEntity = m_History[m_HistoryIndex];
		}
	}

}
