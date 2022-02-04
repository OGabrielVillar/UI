#pragma once
#include "Rect.h"

namespace Hazel::Geometry {

	template <typename T>
	_NODISCARD constexpr bool HitTest(const Template::Rect<T>& a, const Template::Rect<T>& b) {

		const T a_t = a.y;
		const T a_l = a.x;
		const T a_b = a.y + a.height;
		const T a_r = a.x + a.width;

		const T b_t = b.y;
		const T b_l = b.x;
		const T b_b = b.y + b.height;
		const T b_r = b.x + b.width;

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

}


//if (aTL_in.x > bBR_in.x)
//return false;
//if (aBR_in.x < bTL_in.x)
//	return false;
//if (aTL_in.y > bBR_in.y)
//return false;
//if (aBR_in.y < bTL_in.y)
//	return false;
