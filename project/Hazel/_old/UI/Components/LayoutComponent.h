#pragma once

#include "Hazel/UI/UIComponent.h"
#include "Core/Flags.h"
#include "Hazel/UI/LayoutSnap.h"

namespace Hazel::UI {
	
//[Layout Flags]
	enum class LayoutFlags : uint8_t {
		  Active = BIT8(0),
		Cropable = BIT8(1),
	};

//[Layout]
	struct Layout {
	 //[Type Definitions]
		using Flags = Flags<LayoutFlags>;


		glm::vec2 size = { 0.f , 0.f };
		glm::vec2 offset = { 0.f , 0.f };
		LayoutSnap snap_my = LayoutSnap::TopLeft;
		LayoutSnap snap_to = LayoutSnap::TopLeft;
		Flags m_flags;

		glm::vec2 crop_max = { 0.f , 0.f };
		glm::vec2 crop_min = { 0.f , 0.f };
	};

//[Layout Component]
	struct LayoutComponent : public UI::Component {
	 public:
	 //[Constructors]
		LayoutComponent()
			: Component(ComponentType::Layout) {}
		virtual ~LayoutComponent() = default;
		LayoutComponent(const LayoutComponent& other) = default;

	 public:
	 //[Setters Functions]
		void SetOffset(float x, float y);
		void SetSize(float x, float y);

	 //[Getter Functions]
		const glm::vec2& GetTopLeft() const { return tl; }
		const glm::vec2& GetSize() const { return layout.size; }

	 private:
	 //[Auto Functions]
		void RecalculateTopLeft() { // TEMPORALY
			tl = layout.offset;
		}
		void RecalculateBottonRight() { // TEMPORALY
			br = layout.offset + layout.size;
		}

	 //[Internal Members]
		Layout layout;
		LayoutComponent* archor_to = nullptr;

	 //[Auto Members]
		glm::vec2 tl = { 0.f , 0.f }; // Distance of the top left corner of the main window to the top left corner of layout.
		glm::vec2 br = { 0.f , 0.f }; // Distance of the top left corner of the main window to the botton right corner of layout.

	};

}

