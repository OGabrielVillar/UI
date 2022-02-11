#include <Hazel.h>
#include <Hazel/Run/Entry.h>

#include "EditorApp.h"

Hazel::Application* Hazel::CreateApplication()
{

	return new EditorApp("Hazel Editor");

}
