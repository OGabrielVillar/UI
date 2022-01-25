#pragma once

#include "Hazel/UI/UIComponent.h"
#include "Core/Flags.h"

namespace Hazel::UI {

//[Button Flags]
	enum class ButtonFlags : uint8_t {
		   Active = BIT8(0),
		 Hoverble = BIT8(1),
		Pressable = BIT8(2),
	};
	
//[Button State]
	enum class ButtonState : uint8_t {
		Non            = 0,
		OnHover        = 1,
		OnPressInward  = 2, // Pressing inside the ui element hitbox.
		OnPressOutward = 3, // Pressing outside the ui element hitbox.
	};

//[Button Visual]
	struct ButtonVisual {
		glm::vec4 Color;
		glm::vec4 OnHoverColor;
		glm::vec4 OnPressInColor;
		glm::vec4 OnPressOutColor;
		glm::vec4 UnpressableColor;
	};

//[Button Component]
	struct ButtonComponent : public Component
	{
	 public:
		ButtonComponent()
			: Component(ComponentType::Button) {}

	 //[Setters Functions]
		void SetFlagsTo(const ButtonFlags flags_in) { m_flags.SetTo(flags_in); }
		void OnHover() {}
		void OnPress() {}

	 //[Getters Functions]
		const ButtonState& GetState() const { return m_state; }
		bool IsInHover() { return m_state == ButtonState::OnHover; }
		bool IsInPress() { return m_state == ButtonState::OnPressInward || m_state == ButtonState::OnPressOutward; }
		bool IsHoverble() { return m_flags.Contains(ButtonFlags::Hoverble); }
		bool IsPressable() { return m_flags.Contains(ButtonFlags::Pressable); }

	 public:
	 //[Type Definitions]
		using Flags = Flags<ButtonFlags>;
		using State = ButtonState;
		using Visual = ButtonVisual;

	 private:
	 //[Internal Members]
		Flags m_flags;
		State m_state = State::Non;
		Visual m_visual;
	};

}
