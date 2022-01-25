#pragma once
#include "../Math/MathCommon.h"
#include "Angle.h"

namespace Hazel::Geometry {

	// 3D

	struct transform3 {
	 public:
		transform3() = default;

		// Operators
		 //transform vec3
		vec3 operator*(const vec3& vec_in) { 
			const vec4 result = vec4({ vec_in.x , vec_in.y , vec_in.z , 1.f }) * get_matrix();
			return *(vec3*)&result;
		}

		// Getters
		const vec3& get_position() const { return position; }
		const vec3& get_euler() const { return euler; }
		const quaternion& get_quaternion() const { return rotation; }
		const vec3& get_scale() const { return scale; }
		const mat4& get_matrix() {
			if (recalculation_need)
				recalculate_matrix();
			return matrix;
		}
		const mat4& mat() {	return get_matrix(); }

		// Setters
		void set_position(const vec3& position_in)
		{
			position = position_in;

			recalculation_need = true;
		}
		void set_rotation(const vec3& euler_in)
		{
			rotation = { 1.f , 0.f , 0.f , 0.f };
			rotation = glm::rotate(rotation, glm::radians(euler_in.x), { 1 , 0 , 0 });
			rotation = glm::rotate(rotation, glm::radians(euler_in.y), { 0 , 1 , 0 });
			rotation = glm::rotate(rotation, glm::radians(euler_in.z), { 0 , 0 , 1 });

			euler = euler_in;

			recalculation_need = true;
		}
		void set_x_rotation(float degrees_in)
		{
			rotation = glm::rotate(rotation, glm::radians(degrees_in - euler.x), { 1 , 0 , 0 });

			euler.x = degrees_in;

			recalculation_need = true;
		}
		void set_y_rotation(float degrees_in)
		{
			rotation = glm::rotate(rotation, glm::radians(degrees_in - euler.y), { 0 , 1 , 0 });

			euler.y = degrees_in;

			recalculation_need = true;
		}
		void set_z_rotation(float degrees_in)
		{
			rotation = glm::rotate(rotation, glm::radians(degrees_in - euler.z), { 0 , 0 , 1 });

			euler.z = degrees_in;

			recalculation_need = true;
		}
		void set_scale(const vec3& scale_in)
		{
			scale = scale_in;

			recalculation_need = true;
		}

		// Utility
		std::string ToString() {
			std::stringstream ss;
			ss << "[Position]\n  x["     << position.x << "] y[" << position.y << "] z[" << position.z << "]\n"
			   << "[Rotation]\n  x["  << euler.x    << "] y[" << euler.y    << "] z[" << euler.z    << "]\n"
			   << "[Scale]\n  x["        << scale.x    << "] y[" << scale.y    << "] z[" << scale.z    << "]" ;
			return ss.str();
		}

	 private: // Auto
		void recalculate_matrix()
		{
			matrix = glm::translate(mat4(1.f), position);
			matrix *= rotation.operator glm::mat<4, 4, glm::f32, glm::packed_highp>();
			matrix = glm::scale(matrix, scale);

			recalculation_need = false;
		}

	 private: // Members
		vec3 position = { 0.f , 0.f , 0.f };
		quaternion rotation = { 1.f , 0.f , 0.f , 0.f };
		vec3 scale = { 1.f , 1.f , 1.f };
		vec3 euler = glm::eulerAngles(rotation);
		mat4 matrix = mat4(1.f);

		bool recalculation_need = false;
	};

	// 2D

	struct transform2 {
	 public:
		transform2() = default;

		// Operators
		 //transform vec3
		vec2 operator*(const vec2& vec_in) {
			const vec3 result = vec3({ vec_in.x , vec_in.y, 1.f }) * get_matrix();
			return (vec2)result;
		}

		// Getters
		const vec2& get_position() const { return position; }
		const angle& get_rotation() const { return rotation; }
		const vec2& get_scale() const { return scale; }
		const mat3& get_matrix() {
			if (recalculation_need)
				recalculate_matrix();
			return matrix;
		}
		const mat3& mat() { return get_matrix(); }

		// Setters
		void set_position(const vec2& position_in)
		{
			position = position_in;

			recalculation_need = true;
		}
		void set_rotation(degree degree_in)
		{
			rotation = angle(degree_in);

			degrees = degree_in;

			recalculation_need = true;
		}
		void set_scale(const vec2& scale_in)
		{
			scale = scale_in;

			recalculation_need = true;
		}

		// Utility
		std::string ToString() {
			std::stringstream ss;
			ss << "[Position]\n  x[" << position.x << "] y[" << position.y << "]\n"
			   << "[Rotation]\n  degrees[" << degrees << "]\n"
			   << "[Scale]\n  x["    << scale.x    << "] y[" << scale.y    << "]";
			return ss.str();
		}

	private: // Auto
		void recalculate_matrix()
		{
			matrix = { rotation.cos * scale.x , -rotation.sin , position.x
					 , rotation.sin , rotation.cos * scale.y , position.y
					 , 0.f , 0.f , 1.f};

			//matrix = mat3(1.f);
			//matrix[2][0] = position.x;
			//matrix[2][1] = position.y;
			//matrix[0][0] = rotation.cos;
			//matrix[0][1] = -rotation.sin;
			//matrix[1][0] = rotation.sin;
			//matrix[1][1] = rotation.cos;
			//matrix[0][0] *= scale.x;
			//matrix[1][1] *= scale.y;

			recalculation_need = false;
		}

	private: // Members
		vec2 position = { 0.f , 0.f };
		angle rotation;
		vec2 scale = { 1.f , 1.f };
		float degrees;
		mat3 matrix = mat3(1.f);

		bool recalculation_need = false;
	};
}
