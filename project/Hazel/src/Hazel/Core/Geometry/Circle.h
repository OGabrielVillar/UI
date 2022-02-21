#pragma once

#include "GeometryCommon.h"

namespace Hazel::Geometry
{

	namespace Template {

		template<uint32_t dimensions, typename type = float>
		struct Circle {
			type radius;
			glm::vec<dimensions,type> center;
		};

	}
	using Circle = Template::Circle<2>;
	using Sphere = Template::Circle<3>;

}
