#include <Hazel.h>
#include <Hazel/Run/Entry.h>

#include "EditorApp.h"

Hazel::Application* Hazel::CreateApplication()
{

	//return new EditorApp("Hazel Editor", Hazel::Window::Flag::Transparent | Hazel::Window::Flag::Focused);
	return new EditorApp("Hazel Editor", Window::Flag::Decorated | Hazel::Window::Flag::Focused);

}
