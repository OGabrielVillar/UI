#include "pch.h"
#include "Slider.h"

namespace Hazel {

    bool Slider::OnSlide()
    {
		if (f_OnSlide)
			return (*f_OnSlide)();
		return false;
    }

}
