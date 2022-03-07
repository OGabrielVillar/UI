#pragma once

#include "KeyboardCodes.h"

namespace Hazel 
{

	class Keyboard {
	public:
		using Key = KeyCode;
		using Modifier = KeyModifier;
		using Action = KeyAction;
		using Modifiers = Flags<KeyModifier>;
	};

}
