#pragma once

#include "Hazel/Input/InputSignal.h"
#include "Hazel/Input/Event.h"
#include "Hazel/Input/Device/KeyEvent.h"
#include "Hazel/Input/Device/MouseEvent.h"

namespace Hazel {


	inline InputSignal ToInputSignal(Event& e) {

		EventDispatcher dispatcher(e);
		switch (e.GetEventType())
		{
			case(EventType::KeyPressed):
			{
				InputCode ic;
				dispatcher.Dispatch<KeyPressedEvent>([&ic](KeyPressedEvent& event) {
					ic.value = to_underlying(event.GetKeyCode());
					return true;
					});
				ic.action = InputAction::KeyboardKeyPress;
				return InputSignal(ic);
			}
				break;
			case(EventType::KeyReleased):
			{
				InputCode ic;
				dispatcher.Dispatch<KeyReleasedEvent>([&ic](KeyReleasedEvent& event) {
					ic.value = to_underlying(event.GetKeyCode());
					return true;
					});
				ic.action = InputAction::KeyboardKeyRelease;
				return InputSignal(ic);
			}
			break;
			case(EventType::MouseButtonPressed):
			{
				InputCode ic;
				dispatcher.Dispatch<MouseButtonPressedEvent>([&ic](MouseButtonPressedEvent& event) {
					ic.value = event.GetMouseButton();
					return true;
					});
				ic.action = InputAction::MouseButtonPress;
				return InputSignal(ic);
			}
			break;
			case(EventType::MouseButtonReleased):
			{
				InputCode ic;
				dispatcher.Dispatch<MouseButtonReleasedEvent>([&ic](MouseButtonReleasedEvent& event) {
					ic.value = event.GetMouseButton();
					return true;
					});
				ic.action = InputAction::MouseButtonRelease;
				return InputSignal(ic);
			}
				break;
			case(EventType::MouseMoved):
			{
				InputMovement im;
				dispatcher.Dispatch<MouseMovedEvent>([&im](MouseMovedEvent& event) {
					im.value = { event.GetX(), event.GetY(), 0.0f, 0.0f };
					return true;
					});
				im.action = InputAction::MouseMove;
				return InputSignal(im);
			}
				break;
			case(EventType::MouseScrolled):
			{
				InputScroll is;
				dispatcher.Dispatch<MouseScrolledEvent>([&is](MouseScrolledEvent& event) {
					is.value = { event.GetXOffset(), event.GetYOffset() };
					return true;
					});
				is.action = InputAction::MouseScroll;
				return InputSignal(is);
			}
			break;

		}
	}

}