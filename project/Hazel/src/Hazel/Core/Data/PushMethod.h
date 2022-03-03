#pragma once

namespace Hazel::Data {
	enum class PushMethod : unsigned char {
		Over,
		Under,
		OverCurrent,
		UnderCurrent,
	};
}
