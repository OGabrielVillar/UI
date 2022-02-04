#pragma once

#include "../Math/MathCommon.h"

namespace Hazel::Geometry {

	namespace Template
	{

		template <typename T>
		struct Rect {
			constexpr Rect() = default;
			constexpr Rect(const Rect& other) = default;
			constexpr Rect(T left_in, T right_in, T top_in, T bottom_in)
				: left(left_in),
				  top(top_in),
				  right(right_in),
				  bottom(bottom_in)
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
			union {
				T w = 0.f;
				T r;
				T right;
			};
			union {
				T z = 0.f;
				T b;
				T bottom;
			};
			T width() { return w - x; };
			T height() { return z - y; };

		 public:
			inline static Rect<T> LTRB(T left, T top, T right, T bottom)
			{ return Rect(left, right, top, bottom); }
			inline static Rect<T> XYWH(T x, T y, T width, T height)
			{ return Rect(x, x+width, y, y+height); }
		};

	}

	using Rect = Template::Rect<float>;
	using intRect = Template::Rect<int>;

}
