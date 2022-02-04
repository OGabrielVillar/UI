#pragma once

#include "Hazel/UI/UILayer.h"

#include "Hazel/UI/Components/FrameComponent.h"
#include "Hazel/UI/Components/ButtonComponent.h"

// Avoiding Windows.h "CreateWindow" global definition.
#ifdef HZ_PLATFORM_WINDOWS
#define WindowsCreateWindow CreateWindow
#undef CreateWindow
#endif

namespace Hazel::UI {

	static UILayer* worklayer;

	struct WorkInLayer {
		WorkInLayer(UILayer& uilayer) { worklayer = &uilayer; }
	};

	inline UI::Element CreateFrame(const std::string& name) {

		auto& element = worklayer->CreateElement(name);

		element.AddComponent<FrameComponent>();

		return element;
	}

	inline UI::Element CreateButton(const std::string& name) {

		auto& element = worklayer->CreateElement(name);

		element.AddComponent<ButtonComponent>();
		
		return element;
	}

	inline UI::Element CreateWindow(const std::string& name) {

		// Window Frame
		auto& element = worklayer->CreateElement(name);
		element.AddComponent<FrameComponent>();

		// Window Frame
		auto& element = worklayer->CreateElement(name);
		element.AddComponent<FrameComponent>();

		return element;
	}

}