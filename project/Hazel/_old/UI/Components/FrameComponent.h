#pragma once

#include "Hazel/UI/UIComponent.h"

namespace Hazel::UI {

//[Frame Visual]
	struct FrameVisual {
		glm::vec4 Color;
	};

//[Frame Component]
	struct FrameComponent : public UI::Component
	{
	 public:
		FrameComponent()
			: Component(ComponentType::Frame) {}

	 //[Setter Functions]
		void SetColor( float r, float g, float b, float a = 1.f) { 
			m_visual.Color.r = r; 
			m_visual.Color.g = g;
			m_visual.Color.b = b;
			m_visual.Color.a = a;
		}
	 //[Getter Functions]
		const FrameVisual& GetVisual() const { return m_visual; }
		bool IsVisible() const { return visible; }


	 public:
	 //[Type Definitions]
		using Visual = FrameVisual;

	 private:
	 //[Internal Members]
		bool visible = true;
		Visual m_visual;
	};

}
