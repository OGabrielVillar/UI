#pragma once

namespace Hazel {

	enum class ButtonFlag : uint8_t {
		Innactive = BIT(0),
		Hidden    = BIT(1),
		Focused   = BIT(2),
	};

	enum class ButtonState : uint8_t {
		Inert,
		Pressing,
	};

	class Button {
	public:
		using State = ButtonState;
		using Flag = ButtonFlag;
		using Flags = Flags<Flag>;

	public:
		bool OnPress();
		bool OnRelease();
		bool OnHoverIn();
		bool OnHoverOut();
		
		inline bool IsActive() const { return m_Flags.NotContains(Flag::Innactive); }

	private:
		Flags m_Flags;
		bool m_IsHovering;

		Ref<std::function<bool()>> f_OnPress;
		Ref<std::function<bool()>> f_OnRelease;
		Ref<std::function<bool()>> f_OnHoverIn;
		Ref<std::function<bool()>> f_OnHoverOut;
	};

	class ButtonComponent : public Button {};

}
