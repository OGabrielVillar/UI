#pragma once
#include "pch.h"

namespace Hazel::Math {

	template<typename T>
	inline constexpr T PositiveModulo(const T a, const T b) 
	{
		if(b == 0) return 0;
		int c;
		a < 0 ? c = b - ( (a * T(-1)) % b ): c = a % b;
		c %= b;
		return c;
	}

	const float pi = glm::pi<float>();

	using vec2 = glm::vec2;
	using vec2int = glm::vec<2, int>;
	using vec2uint = glm::vec<2, unsigned int>;
	using vec3 = glm::vec3;
	using vec4 = glm::vec4;
	using mat3 = glm::mat3;
	using mat4 = glm::mat4;
	using u8vec2 = glm::u8vec2;
	using u8vec3 = glm::u8vec3;
	using u8vec4 = glm::u8vec4;
	
	using quaternion = glm::quat;

	using rgb = glm::vec3;
	using rgba = glm::vec4;
	using u8rgb = glm::u8vec3;
	using u8rgba = glm::u8vec4;

}
