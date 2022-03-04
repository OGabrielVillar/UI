#pragma once
#include "Rect.h"

namespace Hazel {

	template <typename T>
	constexpr bool HitTest(const Geometry::Template::AABBRect<T>& a, const Geometry::Template::AABBRect<T>& b) {

		const T a_l = a.a_x;
		const T a_t = a.a_y;
		const T a_r = a.b_x;
		const T a_b = a.b_y;

		const T b_l = b.a_x;
		const T b_t = b.a_y;
		const T b_r = b.b_x;
		const T b_b = b.b_y;

		if (a_l > b_r)
			return false;
		if (a_r < b_l)
			return false;
		if (a_t > b_b)
			return false;
		if (a_b < b_t)
			return false;

		return true;
	}

	template <typename T>
	constexpr bool HitTest(const glm::vec<2,T>& a, const Geometry::Template::AABBRect<T>& rect) {

		if (a.x < rect.a_x)
			return false;
		if (a.x > rect.b_x)
			return false;
		if (a.y < rect.a_y)
			return false;
		if (a.y > rect.b_y)
			return false;

		return true;
	}

}
