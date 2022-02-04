#include <Hazel.h>
#include <Hazel/Run/Entry.h>

class EditorApp : public Hazel::Application {
 public:
	EditorApp() {}
};

Hazel::Application* Hazel::CreateApplication()
{

	return new EditorApp();

}
