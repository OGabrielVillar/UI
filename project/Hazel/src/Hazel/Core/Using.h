#pragma once

namespace Hazel {
	
	// [Definitions]
	
	// Data
		template <unsigned int size, typename type>
		using Buffer = Data::Buffer<size,type>;
		
	//Containers
		template <typename T>
		using Stack = Containers::Stack<T>;
	// Text
		using string = std::string;

	// Math & Geometry
		using vec2 = Math::vec2;
		using vec3 = Math::vec3;
		using vec4 = Math::vec4;
		using mat3 = Math::mat3;
		using mat4 = Math::mat4;
		using u8vec2 = Math::u8vec2;
		using u8vec3 = Math::u8vec3;
		using u8vec4 = Math::u8vec4;

		using quaternion = Math::quaternion;
		
		const float pi = Math::pi;

		using Rect = Geometry::Rect;
		using intRect = Geometry::intRect;
	
	 
	// Visuals
		using rgb = Math::vec3;
		using rgba = Math::vec4;
		using u8rgb = Math::u8vec3;
		using u8rgba = Math::u8vec4;
	
	//Time
		using namespace Time::Literals;
		using Time::Timer;

}
