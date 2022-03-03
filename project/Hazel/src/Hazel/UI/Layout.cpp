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
	}

	void Layout::SetPosition(const vec2& position)
	{
		m_Rect.SetPosition(position);
	}

	void Layout::SetAnchor(Anchor anchor)
	{
		m_Anchor = anchor;
	}

	void Layout::SetAX(float value)
	{
		m_Rect.a_x = value;
	}

	void Layout::SetAY(float value)
	{
		m_Rect.a_y = value;
	}

	void Layout::SetBX(float value)
	{
		m_Rect.b_x = value;
	}

	void Layout::SetBY(float value)
	{
		m_Rect.b_y = value;
	}

	void Layout::SetSnap(Snap snap)
	{
		m_Snap = snap;
	}

	Rect Layout::GetRect() const
	{

		if (m_Hierarchy) {
			Rect parentRect;

			auto* parentLayout = m_Hierarchy->GetParent<LayoutComponent>();
			if(!parentLayout)
				parentRect = {0.f,0.f,0.f,0.f};
			else
				parentRect = parentLayout->GetRect();


			vec2 shift(0.f);

			Rect result = m_Rect;

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

			result += shift;

			if (m_Snap.IsSnappingTo(Snap::Left))
				result.a_x = parentRect.a_x;
			if (m_Snap.IsSnappingTo(Snap::Right))
				result.b_x = parentRect.b_x;
			if (m_Snap.IsSnappingTo(Snap::Top))
				result.a_y = parentRect.a_y;
			if (m_Snap.IsSnappingTo(Snap::Bottom))
				result.b_y = parentRect.b_y;

			return result;
		}

		return m_Rect;

	}

}
