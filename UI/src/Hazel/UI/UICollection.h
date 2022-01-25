#pragma once

#include "pch.h"

#include "Hazel/UI/UIComponent.h"
#include "Hazel/Input/CommandCollection.h"
#include "Hazel/UI/UIElement.h"

namespace Hazel::UI {

	class Collection {
	public:
		Collection();

		void OnClick(const InputSignal& code_in);
		void OnOpenOptionsMenu(const InputSignal& code_in);
		void OnMouseMovement(const InputSignal& code_in);
		void OnScroll(const InputSignal& code_in);

		bool RunInput(const InputSignal& code_in);

		//Button AddButton();
		//Frame AddFrame();
	private:
		entt::registry m_registry;
		CommandCollection m_cmds;
	};

}
