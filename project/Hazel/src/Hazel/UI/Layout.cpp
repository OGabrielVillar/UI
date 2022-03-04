#include "pch.h"
#include "Layout.h"

#include "Structure/Components.h"

namespace Hazel {

	void Layout::SetHierarchy(Hierarchy& parent)
	{
		m_Hierarchy = &parent;
	}

	void Layout::SetSize(const vec2& size)
	{
		m_Rect.SetSize(size);
		UpdateChilds();
	}

	void Layout::SetPosition(const vec2& position)
	{
		m_Rect.SetPosition(position);
		UpdateChilds();
	}

	void Layout::SetAnchor(Anchor anchor)
	{
		m_Anchor = anchor;
		UpdateChilds();
	}

	void Layout::SetEdgeSnap(EdgeSnap edgeSnap)
	{
		m_EdgeSnap = edgeSnap;
		UpdateChilds();
	}

	void Layout::UpdateChilds()
	{
		if (m_IsUpToDate)
			m_Hierarchy->BottomToTop([](Entity ent) {
				ent.HaveComponent<LayoutComponent>();
					ent.GetComponent<LayoutComponent>().ParentHasUpdated();
			});
	}

	const Rect& Layout::GetRect() const
	{
		if (!m_IsUpToDate)
			UpdateResultRect();

		return m_ResultRect;
	}

	const Rect& Layout::GetRawRect() const
	{
		return m_Rect;
	}

	void Layout::UpdateResultRect() const
	{
		if (m_Hierarchy) {

			Rect parentRect;

			auto* parentLayout = m_Hierarchy->GetParent<LayoutComponent>();
			if(!parentLayout)
				parentRect = {0.f,0.f,0.f,0.f};
			else
				parentRect = parentLayout->GetRect();


			vec2 shift(0.f);

			m_ResultRect = m_Rect;

			// TODO: Inherit Option

			// From x
			if (m_Anchor.IsFrom(Anchor::X::Center))
				shift.x += (m_Rect.a_x - m_Rect.b_x) / 2.f;
			else if (m_Anchor.IsFrom(Anchor::X::Right))
				shift.x +=  m_Rect.a_x - m_Rect.b_x;

			// To
			if (m_Anchor.IsTo(Anchor::X::Left))
				shift.x += parentRect.a_x;
			else if (m_Anchor.IsTo(Anchor::X::Center))
				shift.x += parentRect.xCenter();
			else if (m_Anchor.IsTo(Anchor::X::Right))
				shift.x += parentRect.b_x;

			// From y
			if (m_Anchor.IsFrom(Anchor::Y::Center))
				shift.y += (m_Rect.a_y - m_Rect.b_y) / 2.f;
			else if (m_Anchor.IsFrom(Anchor::Y::Bottom))
				shift.y += m_Rect.a_y - m_Rect.b_y;

			// To
			if (m_Anchor.IsTo(Anchor::Y::Top))
				shift.y += parentRect.a_y;
			else if (m_Anchor.IsTo(Anchor::Y::Center))
				shift.y += parentRect.yCenter();
			else if (m_Anchor.IsTo(Anchor::Y::Bottom))
				shift.y += parentRect.b_y;

			m_ResultRect += shift;

			if (m_EdgeSnap.IsSnappingTo(EdgeSnap::Left))
				m_ResultRect.a_x = parentRect.a_x;
			if (m_EdgeSnap.IsSnappingTo(EdgeSnap::Right))
				m_ResultRect.b_x = parentRect.b_x;
			if (m_EdgeSnap.IsSnappingTo(EdgeSnap::Top))
				m_ResultRect.a_y = parentRect.a_y;
			if (m_EdgeSnap.IsSnappingTo(EdgeSnap::Bottom))
				m_ResultRect.b_y = parentRect.b_y;

		} else {

			m_ResultRect = m_Rect;

		}

		m_IsUpToDate = true;

	}

}
