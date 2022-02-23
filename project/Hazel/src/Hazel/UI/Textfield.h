#pragma once

namespace Hazel {

	enum class TextfieldFlag : uint8_t {
		Innactive = BIT(0),
		Hidden    = BIT(1),
		Focused   = BIT(2),
	};

	class Textfield {
	 public:
		using Flag = TextfieldFlag;
		using Flags = Flags<Flag>;

	 public:
		bool OnType();

		inline bool IsActive() const { return m_Flags.NotContains(Flag::Innactive); }
		inline bool IsVisible() const { return m_Flags.NotContains(Flag::Hidden); }

	 private:
		Flags m_Flags;

		std::string m_String;

		Ref<std::function<bool()>> f_OnType;
	};

	struct TextfieldComponent : public Textfield {};

}
