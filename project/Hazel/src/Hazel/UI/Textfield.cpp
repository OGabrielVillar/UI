#include "pch.h"
#include "Textfield.h"

namespace Hazel {
    bool Textfield::OnType()
    {
		if (f_OnType)
			return (*f_OnType)();
		return false;
    }
}
