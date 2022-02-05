#include "pch.h"
#include "Command.h"

namespace Hazel {

	void CommandExample() {
		Command cmd("click", MouseButtonEvent(MouseCode::Right, MouseAction::Press));
		cmd.SetFunction<MouseButtonEvent>([](const MouseButtonEvent* event) { 
			return true; 
		});
	}

}
