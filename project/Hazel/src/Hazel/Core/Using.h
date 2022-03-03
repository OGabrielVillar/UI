#pragma once

namespace Hazel {
	
	// [Definitions]
	
	//Functional
		template<typename Return, typename ...Args>
		using Function = Return(*)(Args...);

		template<typename T, typename Return, typename ...Args>
		using FunctionOf = Return(T::*)(Args...);

	//Data
		template <typename T>
		using Stack = Data::Stack<T>;

		template <typename T>
		using Tree = Data::Tree<T>;

		using Data::SliderEnumeration;
		using Data::Flags;
		using Data::UUID;

	// Text
		using string = std::string;

	// Math & Geometry
		using Math::vec2int;

		using Math::vec2;
		using Math::vec3;
		using Math::vec4;
		using Math::mat3;
		using Math::mat4;
		using Math::u8vec2;
		using Math::u8vec3;
		using Math::u8vec4;

		using Math::quaternion;
		
		const float pi = Math::pi;

		using Geometry::Rect;
		using Geometry::intRect;

		using Geometry::Circle;
		using Geometry::Sphere;
	
	 
	// Visuals
		using rgb = vec3;
		using rgba = vec4;

		using rgb_u8 = glm::vec<3, uint8_t>;
		using rgba_u8 = glm::vec<4, uint8_t>;

		inline static vec4 to_rgb(const rgba_u8& color)
		{
			return (vec4)color / vec4(255.f,255.f,255.f,255.f);
		}
	
	//Time
		using namespace Time::Literals;
		using Time::Timer;

}
