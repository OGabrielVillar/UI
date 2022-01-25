#pragma once

#include "pch.h"

#include "GeometryCommon.h"

namespace Hazel::Geometry {

	struct radians {
		constexpr radians(float in)
			: value(in)
		{}
		operator float() {
			return value;
		}
		float value;
	};
	struct degree {
		constexpr degree(float in)
			: value(in)
		{}
		operator float() {
			return value;
		}
		float value;
	};

	struct angle {
	public:
		angle()
			: x(1.0f), y(0.0f)
		{}
		angle(float x_in, float y_in)
			: x(x_in), y(y_in)
		{}
		angle(radians rad_in)
			: x(std::cos(rad_in)), y(std::sin(rad_in))
		{}
		angle(degree deg_in)
			: x(std::cos(deg_in* glm::pi<float>() / 180.f)), y(std::sin(deg_in* glm::pi<float>() / 180.f))
		{}

	public:
		float radians() const {
			return std::atan2(y, x);
		}
		float degree() const {
			return std::atan2(y, x) * 180.f / glm::pi<float>();
		}
		const vec2& vec() const {
			return *(glm::vec2*)this;
		}
		mat3 mat() {
			mat3 m = mat3(1.f);
			m[0][0] =  cos;
			m[0][1] = -sin;
			m[1][0] =  sin;
			m[1][1] =  cos;
			return m;
		}
		angle& normalize() {
			float len(std::sqrt(x * x + y * y));
			if (len != 0.0f)
			{
				x *= (1.0f / len);
				y *= (1.0f / len);
			}
			return *this;
		}
		angle& operator+=(const angle& in) {
			x = x * in.x - y * in.y;
			y = x * in.y + y * in.x;
			normalize();
			return *this;
		}

	public:
		union
		{
			float x;
			float cos;
		};
		union
		{
			float y;
			float sin;
		};
	};

	//ANGLE FUNCTIONS
	inline angle invert(const angle& angle_in) {
		return angle(angle_in.x, -angle_in.y);
	}
	inline angle rotate(const angle& angleA_in, const angle& angleB_in) {
		return angle(angleA_in.x * angleB_in.x - angleA_in.y * angleB_in.y,
			angleA_in.x * angleB_in.y + angleA_in.y * angleB_in.x);
	}
	inline angle operator+(const angle& angleA_in, const angle& angleB_in) {
		return rotate(angleA_in, angleB_in);
	}
	inline angle operator-(const angle& angle_in) {
		return invert(angle_in);
	}

	//VEC2 FUNCTIONS
	inline vec2 rotate(const vec2& vec_in, const angle& angle_in) {
		return vec2(
			vec_in.x * angle_in.cos - vec_in.y * angle_in.sin ,
			vec_in.x * angle_in.sin + vec_in.y * angle_in.cos
		);
	}

	////MAT4 FUNCTIONS
	//inline vec2 operator*(vec2 vec_in, mat4 mat_in) {
	//	const vec2 i = mat_in[0];
	//	const vec2 j = mat_in[1];
	//	const vec2 slope = mat_in[3];
	//
	//	vec2 result;
	//	result.x = vec_in.x * i.x + vec_in.y * j.x;
	//	result.y = vec_in.x * i.y + vec_in.y * j.y;
	//	result += slope;
	//	return result;
	//}
	//inline void rotate(mat4& mat_in, const angle& angle_in) {
	//	float const c = angle_in.c;
	//	float const s = angle_in.s;
	//
	//	vec3 axis(0.f, 0.f, 1.f);
	//	vec3 temp((1.f - c) * axis);
	//
	//	mat4 Rotate;
	//	Rotate[0][0] = c + temp[0] * axis[0];
	//	Rotate[0][1] = temp[0] * axis[1] + s * axis[2];
	//	Rotate[0][2] = temp[0] * axis[2] - s * axis[1];
	//
	//	Rotate[1][0] = temp[1] * axis[0] - s * axis[2];
	//	Rotate[1][1] = c + temp[1] * axis[1];
	//	Rotate[1][2] = temp[1] * axis[2] + s * axis[0];
	//
	//	Rotate[2][0] = temp[2] * axis[0] + s * axis[1];
	//	Rotate[2][1] = temp[2] * axis[1] - s * axis[0];
	//	Rotate[2][2] = c + temp[2] * axis[2];
	//
	//	mat4 Result;
	//	Result[0] = mat_in[0] * Rotate[0][0] + mat_in[1] * Rotate[0][1] + mat_in[2] * Rotate[0][2];
	//	Result[1] = mat_in[0] * Rotate[1][0] + mat_in[1] * Rotate[1][1] + mat_in[2] * Rotate[1][2];
	//	Result[2] = mat_in[0] * Rotate[2][0] + mat_in[1] * Rotate[2][1] + mat_in[2] * Rotate[2][2];
	//	Result[3] = mat_in[3];
	//	mat_in = Result;
	//}

}

namespace Hazel::Geometry_Literals {

	// radian literal
	_NODISCARD constexpr Geometry::radians operator"" _radians(long double _Val) noexcept /* strengthened */ {
		return Geometry::radians((float)_Val);
	}
	// arcdegree literal
	_NODISCARD constexpr Geometry::degree operator"" _degree(long double _Val) noexcept /* strengthened */ {
		return Geometry::degree((float)_Val);
	}

}

namespace Hazel {
	using namespace Geometry_Literals;
}
