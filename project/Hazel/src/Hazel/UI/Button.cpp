#include "pch.h"
#include "Button.h"

namespace Hazel {

	bool Button::OnPress()
	{
		if (f_OnPress)
			return (*f_OnPress)();
		return false;
	}

	bool Button::OnRelease()
	{
		if (f_OnRelease)
			return (*f_OnRelease)();
		return false;
	}

	bool Button::OnHoverIn()
	{
		if (f_OnHoverIn)
			return (*f_OnHoverIn)();
		return false;
	}

	bool Button::OnHoverOut()
	{
		if (f_OnHoverOut)
			return (*f_OnHoverOut)();
		return false;
	}

}
