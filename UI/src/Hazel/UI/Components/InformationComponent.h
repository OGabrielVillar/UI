#pragma once

#include "Hazel/UI/UIComponent.h"

namespace Hazel::UI {

	class InformationComponent : public UI::Component {
	 public:
		 InformationComponent(const std::string& name)
			: Component(ComponentType::Information) , m_name(name) {}

		void SetName(const std::string& name) { m_name = name; }
		const std::string& GetName() { return m_name; }

	 private:
		std::string m_name;
	};

}