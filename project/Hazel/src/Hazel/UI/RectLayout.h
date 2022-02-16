#pragma once
/*

	4bits represents a anchor point

		0101 1001 1101
		0110 1010 1110
		0111 1011 1111

	1byte represents 2 anchor points,
		one for the "from point",
		another for the "to point".

*/

#include "Core/Geometry/Rect.h"

//using uint8_t = unsigned char;

namespace Hazel {

	class Anchor 
	{
	public:
		enum X : uint8_t 
		{
			Left = 0b00000100,
			Center = 0b00001000,
			Right = 0b00001100
		};
		enum Y : uint8_t 
		{
			Top = 0b00000001,
			Center = 0b00000010,
			Bottom = 0b00000011
		};
		enum class XY : uint8_t 
		{
			LeftTop      = X::Left   | Y::Top,
			LeftCenter   = X::Left   | Y::Center,
			LeftBottom   = X::Left   | Y::Bottom,
			CenterTop    = X::Center | Y::Top,
			CenterCenter = X::Center | Y::Center,
			CenterBottom = X::Center | Y::Bottom,
			RightTop     = X::Right  | Y::Top,
			RightCenter  = X::Right  | Y::Center,
			RightBottom  = X::Right  | Y::Bottom,
		};
		using enum XY;

	public:
		constexpr Anchor(XY anchor = LeftTop, XY to = LeftTop)
			: m_Anchors((uint8_t)anchor | ((uint8_t)to << 4))
		{}

		template<typename TYPE> 
		Geometry::Template::AABBRect<TYPE>& Transform(Geometry::Template::AABBRect<TYPE>& rect)
		{
			
		}

	private:
		uint8_t m_Anchors;
	};

}
