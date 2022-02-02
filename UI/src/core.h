#pragma once

#include "Core/Flags.h"
#include "Core/ThreadLock.h"

#include "Core/Data/Buffer.h"

#include "Core/Containers/Stack.h"

#include "Core/Math/MathCommon.h"
#include "Core/Math/Random.h"

#include "Core/Time/TimeCommon.h"
#include "Core/Time/Timer.h"

#include "Core/Geometry/Angle.h"
#include "Core/Geometry/Rect.h"
#include "Core/Geometry/Collision.h"
#include "Core/Geometry/Transformation.h"

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

		using Rect = Geometry::Rect<float>;
		using intRect = Geometry::Rect<int>;
	
	 
	// Visuals
		using rgb = Math::vec3;
		using rgba = Math::vec4;
		using u8rgb = Math::u8vec3;
		using u8rgba = Math::u8vec4;
	
	//Time
		using namespace Time::Literals;
		using Time::Timer;

	// Pointers
		template<typename T>
		using Scope = std::unique_ptr<T>;
		
		template<typename T, typename ... Args>
		constexpr Scope<T> CreateScope(Args&& ... args)
		{
			return std::make_unique<T>(std::forward<Args>(args)...);
		}

		template<typename T>
		using Reference = std::shared_ptr<T>;
		
		template<typename T, typename ... Args>
		constexpr Reference<T> CreateReference(Args&& ... args)
		{
			return std::make_shared<T>(std::forward<Args>(args)...);
		}
	

}
