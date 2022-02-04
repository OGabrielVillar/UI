#include "pch.h"
#include "LayoutComponent.h"

namespace Hazel::UI {

	void Hazel::UI::LayoutComponent::SetOffset(float x, float y)
	{
		layout.offset.x = x; 

		layout.offset.y = y; 

		RecalculateTopLeft();
	}

	void LayoutComponent::SetSize(float x, float y)
	{
		layout.size.x = x;

		layout.size.y = y;

		RecalculateBottonRight();
	}

}
