#include "pch.h"
#include "UIComponent.h"

#define HZ_CORE_ASSERT(x,y)

namespace Hazel::UI {

 //[UIComponentRequisite]

	ComponentRequisite::ComponentRequisite(ComponentType componentType_in, Condition condition_in)
		: m_condition(condition_in), m_component(componentType_in)
	{}
	
 //[UIComponent]
	void Component::AddRequisite(const ComponentRequisite& requisite_in)
	{
		for (ComponentRequisite& r : m_requisites)
			HZ_CORE_ASSERT(requisite_in.m_component == r.m_component, "Trying to add an duplicated component requisite!");
		m_requisites.push_back(requisite_in);
	}

}
