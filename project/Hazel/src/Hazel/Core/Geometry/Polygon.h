#pragma once

#include "GeometryCommon.h"

namespace Hazel::Geometry
{

	template<uint32_t count, uint32_t dimensions, typename type = float>
	struct Polygon {
		Polygon() = default;
		Polygon(type initial)
			: vertices { initial }
		{}
		glm::vec<dimensions,type> vertices[count];
	};

	using Triangle2D = Polygon<3,2>;
	using Triangle3D = Polygon<3,3>;
}
