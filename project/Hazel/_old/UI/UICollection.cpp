#include "pch.h"

#include "UICollection.h"

#include "Hazel/UI/Components/ButtonComponent.h"
#include "Hazel/UI/Components/FrameComponent.h"
#include "Hazel/UI/Components/HeritageComponent.h"
#include "Hazel/UI/Components/LayoutComponent.h"
#include "Hazel/UI/Components/InformationComponent.h"
#include "Hazel/UI/Components/SliderComponent.h"

namespace Hazel::UI {
	Collection::Collection()
	{
		////Click
		//auto& cmd_click = m_cmds.AddCommand();
		//cmd_click.Rename("Click");
		//cmd_click.SetInputSignal(InputSignal(MouseButtonCode::Left,InputAction::MouseButtonPress));
		//cmd_click.SetFunctionWithArgs<const InputSignal&>([&](const InputSignal& code_in) {	OnClick(code_in); });
		////Open Options Menu
		//auto& cmd_openOptionsMenu = m_cmds.AddCommand();
		//cmd_openOptionsMenu.Rename("Open Options Menu");
		//cmd_click.SetInputSignal(InputSignal(MouseButtonCode::Right, InputAction::MouseButtonPress));
		//cmd_openOptionsMenu.SetFunctionWithArgs<const InputSignal&>([&](const InputSignal& code_in) { OnOpenOptionsMenu(code_in); });
		////Mouse Movement
		//auto& cmd_mouseMovement = m_cmds.AddCommand();
		//cmd_mouseMovement.Rename("Mouse Movement");
		//cmd_click.SetInputSignal(InputSignal(InputAction::MouseMove));
		//cmd_mouseMovement.SetFunctionWithArgs<const InputSignal&>([&](const InputSignal& code_in) {	OnMouseMovement(code_in); });
		//Scroll
		//auto& cmd_scroll = m_cmds.AddCommand();
		//cmd_scroll.Rename("Scroll");
		//cmd_scroll.SetInputSignal(InputSignal(InputAction::MouseScroll));
		//cmd_scroll.SetFunctionWithArgs<const InputSignal&>([&](const InputSignal& code_in) { OnMouseMovement(code_in); });
	}

	bool Collection::RunInput(const InputSignal& code_in)
	{
		return m_cmds.RunInput(code_in);
	}

	//Button Collection::AddButton()
	//{
	//	Button button = Button{ m_registry.create(), m_registry };
	//
	//	button.AddComponent<UI::NameComponent>();
	//
	//	button.AddComponent<UI::LayoutComponent>();
	//
	//	button.AddComponent<UI::HeritageComponent>();
	//
	//	return button;
	//}
	
	//Frame Collection::AddFrame()
	//{
	//	Frame frame = Frame{ m_registry.create(), m_registry };
	//
	//	frame.AddComponent<UI::NameComponent>();
	//
	//	frame.AddComponent<UI::LayoutComponent>();
	//
	//	frame.AddComponent<UI::HeritageComponent>();
	//
	//	return frame;
	//}
}
