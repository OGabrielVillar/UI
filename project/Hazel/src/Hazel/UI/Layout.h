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

#include "Structure/Hierarchy.h"

namespace Hazel {

	// --------------
	// --- Anchor ---
	// --------------

	class Anchor 
	{
	public:
		enum class X : uint8_t 
		{
			Inherit = 0,
			Left    = 0b00000100,
			Center  = 0b00001000,
			Right   = 0b00001100,
			From    = 0b00001100,
			To      = 0b11000000
		};
		enum class Y : uint8_t 
		{
			Inherit = 0,
			Top     = 0b00000001,
			Center  = 0b00000010,
			Bottom  = 0b00000011,
			From    = 0b00000011,
			To      = 0b00110000
		};
		enum class XY : uint8_t 
		{
			Inherit      = 0,
			LeftTop      = (uint8_t)X::Left   | (uint8_t)Y::Top,
			LeftCenter   = (uint8_t)X::Left   | (uint8_t)Y::Center,
			LeftBottom   = (uint8_t)X::Left   | (uint8_t)Y::Bottom,
			CenterTop    = (uint8_t)X::Center | (uint8_t)Y::Top,
			CenterCenter = (uint8_t)X::Center | (uint8_t)Y::Center,
			CenterBottom = (uint8_t)X::Center | (uint8_t)Y::Bottom,
			RightTop     = (uint8_t)X::Right  | (uint8_t)Y::Top,
			RightCenter  = (uint8_t)X::Right  | (uint8_t)Y::Center,
			RightBottom  = (uint8_t)X::Right  | (uint8_t)Y::Bottom,
			From         = 0b00001111,
			To           = 0b11110000,
		};
		using enum XY;

	public:
		inline bool IsFrom(XY xy) const { 
			return ((uint8_t)XY::From & m_Anchors) == (uint8_t)xy; 
		}
		inline bool IsTo(XY xy) const { 
			return ((uint8_t)XY::To & m_Anchors) == (uint8_t)xy << 4; 
		}
		inline bool IsFrom(X x) const { 
			return ((uint8_t)X::From & m_Anchors) == (uint8_t)x; 
		}
		inline bool IsTo(X x) const { 
			return ((uint8_t)X::To & m_Anchors) == (uint8_t)x << 4; 
		}
		inline bool IsFrom(Y y) const { 
			return ((uint8_t)Y::From & m_Anchors) == (uint8_t)y; 
		}
		inline bool IsTo(Y y) const { 
			return ((uint8_t)Y::To & m_Anchors) == (uint8_t)y << 4; 
		}

		inline constexpr Anchor(XY from = LeftTop, XY to = LeftTop)
			: m_Anchors((uint8_t)from | ((uint8_t)to << 4))
		{}

	private:
		uint8_t m_Anchors;
	};
	
	// ------------
	// --- EdgeSnap ---
	// ------------

	class EdgeSnap {
		enum class Flag : uint8_t 
		{
			Left   = BIT(0),
			Right  = BIT(1),
			Top    = BIT(2),
			Bottom = BIT(3),
		};
	public:
		using Flags = Flags<Flag>;
		using enum Flag;

		EdgeSnap(Flags flags = Flags())
			: m_Flags(flags)
		{}

		EdgeSnap(Flag flag)
			: m_Flags(flag)
		{}

		void Set(Flags flags, bool to)
		{
			if (to)
				m_Flags.Add(flags);
			else
				m_Flags.Remove(flags);
		}

		bool IsSnappingTo(Flags flags) const
		{
			return m_Flags.Contains(flags);
		}

	private:
		Flags m_Flags;
	};
	
	// --------------
	// --- Layout ---
	// --------------

	class Layout {
	public:
		Layout()
		  : m_Rect({0.f,0.f,0.f,0.f})
		{}
		Layout(const vec2& position, const vec2& size)
		  : m_Rect(Rect::XYWH(position, size))
		{}
		Layout(const Rect& rect, Anchor anchor = Anchor())
		  : m_Rect(rect),
			m_Anchor(anchor)
		{}

		void SetHierarchy(Hierarchy& parent);
		void SetSize(const vec2& size);
		void SetPosition(const vec2& position);
		void SetAnchor(Anchor anchor);
		void SetEdgeSnap(EdgeSnap edgeSnap);

		void UpdateChilds();
		inline void ParentHasUpdated() { m_IsUpToDate = false; }

		Rect GetRect() const;

	private:
		void UpdateResultRect() const;

	private:
		Rect m_Rect;
		Anchor m_Anchor;
		EdgeSnap m_EdgeSnap;

	private: // Hierarchy
		Hierarchy* m_Hierarchy = nullptr;
		mutable Rect m_ResultRect;
		mutable bool m_IsUpToDate = false;
	};
	
	// ------------------------
	// --- Layout Component ---
	// ------------------------

	struct LayoutComponent : public Layout {
		LayoutComponent()
			: Layout()
		{}
		LayoutComponent(const vec2& position, const vec2& size)
			: Layout(position, size)
		{}
		LayoutComponent(const Rect& rect, Anchor anchor = Anchor())
			: Layout(rect, anchor)
		{}
	};

}
