#pragma once

namespace Hazel {

	enum class CursorMode : uint8_t {
		Normal,
		Hidden,
		Disabled,
		Locked,
	};

	struct Cursor 
	{
		using Mode = CursorMode;
		Mode mode;
	};

}
