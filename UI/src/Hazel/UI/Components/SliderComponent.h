#pragma once

#include "Hazel/UI/UIComponent.h"
#include "Core/Flags.h"

namespace Hazel::UI {

//[Slider Flags]
	enum class SliderFlags : uint8_t {
		   Active = BIT8(0),
		 Hoverble = BIT8(1),
		Pressable = BIT8(2),
		Draggable = BIT8(3),
	};
	
//[Slider State]
	enum class SliderState : uint8_t {
		OnHover    = 1,
		OnPressIn  = 2, // Pressing inside the ui element hitbox.
		OnPressOut = 3, // Pressing outside the ui element hitbox.
		OnDragIn   = 4, // Dragging inside the ui element hitbox.
		OnDragOut  = 5, // Dragging outside the ui element hitbox.
	};

//[Slider State]
	enum class SliderOrientation : uint8_t {
		Horizontal,
		Vertical
	};
	
//[Slider Visual]
	struct SliderVisual {
		glm::vec2 KnobSize;
		float TrackWidth;
		glm::vec4 KnobColor;
		glm::vec4 TrackColor;
	};

//[Slider Component]
	class SliderComponent : public UI::Component
	{
	 public: 
		SliderComponent()
			: Component(ComponentType::Slider) {}
	 //[Setters Functions]
		void SetFlagsTo(const SliderFlags flags_in) { m_flags.SetTo(flags_in); }

	 //[Getters Functions]
		const SliderState& GetState() const { return m_state; }
		const SliderOrientation& GetOrientation() const { return m_orientation; }
		bool IsHovering() { return m_state == SliderState::OnHover; }
		bool IsPressing() { return m_state == SliderState::OnPressIn || m_state == SliderState::OnPressOut ; }
		bool IsDragging() { return m_state == SliderState::OnPressIn || m_state == SliderState::OnPressOut; }
		bool IsHoverble() { return m_flags.Contains(SliderFlags::Hoverble); }
		bool IsPressable() { return m_flags.Contains(SliderFlags::Pressable); }

	 public:
	 //[Type Definitions]
		using Flags = Flags<SliderFlags>;
		using State = SliderState;
		using Orientation = SliderOrientation;
		using Visual = SliderVisual;

	 private:
	 //[Internal Members]
		Flags m_flags;
		State m_state;
		Orientation m_orientation;
		Visual m_visual;

	};

}
