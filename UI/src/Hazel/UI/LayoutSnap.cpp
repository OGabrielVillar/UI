#include "pch.h"
#include "LayoutSnap.h"

namespace Hazel::UI {

	void LayoutSnap::InheritX()
	{
		value = value & 0b00001111; // Clear last 4 bits
		value = value | X::Inherit; // Write X::Inherit bits
	}

	void LayoutSnap::InheritY()
	{
		value = value & 0b11110000; // Clear last 4 bits
		value = value | Y::Inherit; // Write X::Inherit bits
	}

	void LayoutSnap::InheritOppositeX()
	{
		value = value & 0b00001111; // Clear last 4 bits
		value = value | X::InheritOpposite; // Write X::Inherit bits
	}

	void LayoutSnap::InheritOppositeY()
	{
		value = value & 0b11110000; // Clear last 4 bits
		value = value | Y::InheritOpposite; // Write X::Inherit bits
	}

}
