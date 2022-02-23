#pragma once

namespace Hazel {

	enum class SliderFlag : uint8_t {
		Innactive   = BIT(0),
		Hidden      = BIT(1),
		Focused     = BIT(2),
		SnapAtSteps = BIT(3),
	};

	enum class SliderType : uint8_t {
		Float,
		Integer,
		Enumeration, // Hashed, StringsValues...
	};

	enum class SliderTrackOrientation : uint8_t {
		BottomToTop,
		TopToBottom,
		LeftToRight,
		RightToLeft,
	};

	class Slider {
	 public:
		using Type = SliderType;
		using Flag = SliderFlag;
		using Flags = Flags<Flag>;

	 public:
		bool OnSlide();

		inline bool IsActive() const { return m_Flags.NotContains(Flag::Innactive); }

	 private:
		Type m_Type;
		Flags m_Flags;
		SliderTrackOrientation m_TrackOrientation;

		struct mType {
			union {
				float float_t;
				int int_t;
			};
		};
		mType m_MaximumValue;
		mType m_MinimumValue;
		mType m_ThumbValue;

		Ref<std::function<bool()>> f_OnSlide; // TODO : Change this, this occupies 64 bytes of memory.
	};

	struct SliderComponent : public Slider {};

}
