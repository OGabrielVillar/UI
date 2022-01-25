#pragma once

#include "Hazel/UI/UIComponent.h"

namespace Hazel::UI {

//[Heritage Component]
	class HeritageComponent : public UI::Component
	{
	 private:
		using Element = entt::entity;
	 public: 
		HeritageComponent() = default;
		HeritageComponent(Element parent_in)
			: Component(ComponentType::Heritage)
			, m_parent(parent_in)
		{}
	 //[Setters Functions]

	 //[Getters Functions]

	 private:
	 //[Internal Members]
		Element m_parent;
		std::vector<Element> m_childs;
	};

}