#include <Hazel.h>
#include <Hazel/Run/Entry.h>

class ClientApp : public Hazel::Application {
public:
	ClientApp(const std::string& name)
		: Application(name)
	{}
	virtual ~ClientApp() = default;

	virtual void OnInit() override {};
	virtual void OnShutdown() override {};
	virtual void OnUpdate() override {};
};

Hazel::Application* Hazel::CreateApplication()
{

	return new ClientApp("Hazel Client");

}
