#pragma once

#include <glm/glm.hpp>

namespace Hazel::UI {

 //[Layout Snap]
	using SnapType = uint8_t;
	class LayoutSnap {
	 public:

		 //[Horizontal Snap Options]
			struct X {
				enum : SnapType
				{			             // BINARY LAYOUT OF X SNAPPING
					           Left = 0, // 0000 0000 Left
					          Right = 1, // 0000 0001 Right
					         Center = 2, // 0000 0010 Center
					        Inherit = 3, // 0000 0011 Inherit
					InheritOpposite = 4  // 0000 0100 InheritOpposite
				};
			};

		 //[Vertical Snap Options]
			struct Y { 
				enum : SnapType
				{							  // BINARY LAYOUT OF Y SNAPPING	
					            Top = 0 << 4, // 0000 0000 Top
					         Botton = 1 << 4, // 0001 0000 Botton
					         Center = 2 << 4, // 0010 0000 Center
					        Inherit = 3 << 4, // 0011 0000 Inherit
					InheritOpposite = 4 << 4  // 0100 0000 InheritOpposite
				};
			};
		 public:

		 //[Easy Snap Options]
			enum : SnapType
			{
				    TopLeft =    Y::Top | X::Left,
				   TopRight =    Y::Top | X::Right,
				        Top =    Y::Top | X::Center,
				 BottonLeft = Y::Botton | X::Left,
				BottonRight = Y::Botton | X::Right,
				     Botton = Y::Botton | X::Center,
				       Left = Y::Center | X::Left,
				      Right = Y::Center | X::Right,
				     Center = Y::Center | X::Center
			};
		
	 public:
		LayoutSnap() = default;
		LayoutSnap(const SnapType in) : value(in) {}

		const LayoutSnap& operator=(const uint8_t rh) { value = rh; return *this; }
		operator uint8_t() { return value; }
		operator const uint8_t() { return value; }
		
	 public:
		void InheritX();
		void InheritY();
		void InheritOppositeX();
		void InheritOppositeY();

	 private:
		 SnapType value = TopLeft;
	};

}