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
	
	 
	// Visuals
		// using rgb = Math::vec3;
		// using rgba = Math::vec4;
		// using u8rgb = Math::u8vec3;
		// using u8rgba = Math::u8vec4;
	
	//Time
		using namespace Time::Literals;
		using Time::Timer;

}
