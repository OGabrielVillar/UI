#pragma once

#include <glm/glm.hpp>
#include <entt/entt.hpp>

namespace Hazel::UI {
	
//[UI Component Type]
	enum class ComponentType : uint16_t {
		Information,
		Layout,
		Heritage,
		Texture,
		Frame,
		Button,
		Slider,
		ScrollRegion,
		Window,
		Font,
		TextLayout,
		EditBox,
	}; 

//[UI Requisite]
	struct ComponentRequisite {
		enum class Condition : uint8_t {
			Have,
			NotHave
		};

		ComponentRequisite(ComponentType componentType_in, Condition condition_in);

		Condition m_condition;
		ComponentType m_component;
	};

//[UI Component]
	struct Component {
	 protected:
		Component() = default;
		Component(ComponentType type)
			: m_type(type) {}
		Component(const Component& other) = default;
		virtual ~Component() = default;

		void AddRequisite(const ComponentRequisite& requisite_in);

	 protected:
		ComponentType m_type;

	 private:
		std::vector<ComponentRequisite> m_requisites;
	};

}