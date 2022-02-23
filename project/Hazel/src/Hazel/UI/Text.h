#pragma once

#include "TextFormatting.h"

namespace Hazel {

	enum class TextFlag : uint8_t {
		Innactive = BIT(0),
		Hidden    = BIT(1),
		Focused   = BIT(2),
	};

	class Text {
	 public:
		using Flag = TextFlag;
		using Flags = Flags<Flag>;

	 public:
		inline bool IsActive() const { return m_Flags.NotContains(Flag::Innactive); }
		inline bool IsVisible() const { return m_Flags.NotContains(Flag::Hidden); }

	 private:
		Flags m_Flags;

		std::string m_String;

		Paragraph m_Paragraph;
	};

	struct TextComponent : public Text {};

}
