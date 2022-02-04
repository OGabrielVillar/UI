#pragma once

#include "GeometryCommon.h"

namespace Hazel::Geometry
{

	template<uint32_t dimensions, typename type = float>
	struct Circle {
		type radius;
		glm::vec<dimensions,type> center;
	};

	using Circle2D = Circle<2>;
	using Circle3D = Circle<3>;

}
