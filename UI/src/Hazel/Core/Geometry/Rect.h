#pragma once
#include "../Math/MathCommon.h"

namespace Hazel::Geometry {

	template <typename T>
	struct Rect {
		constexpr Rect() = default;
		constexpr Rect(T left_in, T top_in, T width_in, T height_in)
			: left(left_in),
			  top(top_in),
			  width(width_in),
			  height(height_in)
		{}
		union {
			T x = 0.f;
			T l;
			T left;
		};
		union {
			T y = 0.f;
			T t;
			T top;
		};
		T width = 0.f, height = 0.f;
	};

}
