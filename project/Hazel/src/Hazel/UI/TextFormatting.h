#pragma once

#include "Layout.h"

namespace Hazel {

	class Paragraph {
	 public:
		enum class Alignment : uint8_t {
			Inherit      = 0,
			LeftTop      = (uint8_t)Anchor::LeftTop,
			LeftCenter   = (uint8_t)Anchor::LeftCenter,
			LeftBottom   = (uint8_t)Anchor::LeftBottom,
			CenterTop    = (uint8_t)Anchor::CenterTop,
			Center       = (uint8_t)Anchor::Center,
			CenterBottom = (uint8_t)Anchor::CenterBottom,
			RightTop     = (uint8_t)Anchor::RightTop,
			RightCenter  = (uint8_t)Anchor::RightCenter,
			RightBottom  = (uint8_t)Anchor::RightBottom,
		};

		enum class HorizontalFit : uint8_t {
			Cut,
			BreakLine,
			Overflow,
			CompressInKerning,
			CompressScale,
		};

		enum class VerticalFit : uint8_t {
			Cut,
			Overflow,
			CompressScale,
		};

	 public:


	 private:
		Alignment m_Alignment;
		HorizontalFit m_HorizontalFit;
		VerticalFit m_VerticalFit;
	};

}
