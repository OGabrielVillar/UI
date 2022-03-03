#include <Hazel.h>

#include "EditorApp.h"
#include "Platform/OpenGL/OpenGLShader.h"

EditorApp::EditorApp(const std::string& name, Hazel::Window::Flags flags) 
	: Application(name, flags)
{}

void EditorApp::OnInit()
{
	InitShit();
}
	
bool EditorApp::OnEvent(const Hazel::Event& event)
{
	return m_Project.OnEvent(event);
}

void EditorApp::OnShutdown() 
{

}

void EditorApp::OnUpdate()
{
	TestShit();
}

void EditorApp::InitShit()
{
	using namespace Hazel;
	PROFILE("InitShit");

	// --- Aspect Ratio
	vec2 resolution = (vec2)m_Window.get()->GetResolution();
	vec2 aspectRatio (resolution / resolution.y);

	vec2 viewportResolution = m_Rect.size();
	vec2 viewportAspectRatio (viewportResolution / viewportResolution.y);
	m_ViewportCanvas->SetSize((vec2int)m_Rect.size());

	// --- Scene Initialization
	m_Camera = m_Project.CreateCamera(aspectRatio);
	m_Scene = CreateReference<Entity>(m_Project.CreateScene(m_Window->GetCanvas()));
	m_Scene->GetComponent<SceneComponent>().SetCamera(m_Camera);

	m_ViewportCamera = m_Project.CreateCamera({viewportAspectRatio});
	m_ViewportScene = CreateReference<Entity>(m_Project.CreateScene(m_ViewportCanvas));
	m_ViewportScene->GetComponent<SceneComponent>().SetCamera(m_ViewportCamera);

	auto commandCardEntity = m_Project.CreateEntity("Command Card");
	auto commandCard = commandCardEntity.AddComponent<CommandCardComponent>();
	
	m_UILayer.GetComponent<LayoutComponent>().SetSize((vec2)m_Window->GetResolution());

	// ----------
	// --- UI ---
	// ----------
	{
		PROFILE("Init UI");

		//auto uiLayerEntity = m_Project.CreateUILayer();

		auto& ui = m_UILayer.GetComponent<UILayerComponent>();

		ui.NewFrame("TitleBar"); {
			ui.SetSize({1920.f,30.f});
			ui.SetAnchor({Anchor::LeftTop, Anchor::LeftTop});
			ui.SetEdgeSnap(EdgeSnap::Right);
			ui.GetMaterial().SetColor(to_rgb({36,36,38,255}));

			ui.NewFrame("CloseButton"); { 
				ui.SetSize({50.f,50.f});
				ui.SetAnchor({Anchor::RightCenter, Anchor::RightCenter});
				ui.GetMaterial().SetColor(to_rgb({64,64,69,255}));

				ui.NewFrame("MinimizeButton"); { 
					ui.SetSize({50.f,50.f});
					ui.SetAnchor({Anchor::RightCenter, Anchor::LeftCenter});
					ui.GetMaterial().SetColor(to_rgb({64,64,69,255}));
				} ui.Close();

			} ui.Close(); 

			m_Movable = ui.NewFrame("TitleLabel"); {
				ui.SetSize({50.f,50.f});
				ui.SetAnchor({Anchor::CenterTop, Anchor::CenterTop});
				ui.GetMaterial().SetColor(to_rgb({64,64,69,255}));

			} ui.Close();

		} ui.Close();

		m_Viewport = CreateReference<Entity>(ui.NewViewport("Viewport")); { 
			ui.SetSize({ 370.f,170.f });
			ui.SetAnchor({ Anchor::RightBottom, Anchor::RightBottom });
			m_Viewport->GetComponent<ViewportComponent>().SetScene(*m_ViewportScene);
		} ui.Close();

	}

	// ----------------
	// --- Commands ---
	// ----------------
	{
		{
			PROFILE("Init Commands");
		
			Ref<Command> cmd;

			cmd = commandCard->AddCommand();
			cmd->SetFunction([this]() 
			{
				m_Movable.GetComponent<LayoutComponent>().SetPosition({90.f,0.f});
				return true;
			});
			cmd->AddTrigger(EventKeyboardKey(Keyboard::Key::Right, Keyboard::Action::Release));
		
			cmd = commandCard->AddCommand();
			cmd->SetFunction([this]() 
			{
				m_Movable.GetComponent<LayoutComponent>().SetPosition({-90.f,0.f});
				return true;
			});
			cmd->AddTrigger(EventKeyboardKey(Keyboard::Key::Left, Keyboard::Action::Release));
		
			cmd = commandCard->AddCommand();
			cmd->SetFunction([this]() 
			{
				m_Texture->SetInterpolation(m_Interpolation[m_InterpolationIndex]);
				m_InterpolationIndex++;
				m_InterpolationIndex %= 2;
				return true;
			});
			cmd->AddTrigger(EventKeyboardKey(Keyboard::Key::F9, Keyboard::Action::Release));
		
			cmd = commandCard->AddCommand();
			cmd->SetFunction([this]() 
			{
				PRINT_PROFILE();
				return false;
			});
			cmd->AddTrigger(EventKeyboardKey(Keyboard::Key::F8, Keyboard::Action::Release));
		
		
			cmd = commandCard->AddCommand();
			cmd->SetFunction<EventCursorPosition>([this](const EventCursorPosition* event) 
			{
				m_TexturePosition = event->position;
				return true;
			});
			cmd->AddTrigger(EventCursorPosition());


			cmd = commandCard->AddCommand();
			cmd->SetFunction<EventMouseScroll>([this](const EventMouseScroll* event) 
			{
				m_ViewportCamera->GetTransform().Scale(1.f - (0.1f * event->offset.y));
				return true;
			});
			cmd->AddTrigger(EventMouseScroll());


			cmd = commandCard->AddCommand();
			cmd->SetFunction<EventWindowSize>([this](const EventWindowSize* event) 
			{
				vec2 resolution = (vec2)event->size;
				vec2 aspectRatio (resolution / resolution.y);
				m_Camera->SetAspectRatio(aspectRatio);
				m_UILayer.GetComponent<LayoutComponent>().SetSize((vec2)event->size);
				return true;
			});
			cmd->AddTrigger(EventWindowSize());
		}//*/

		// --- Texture

		m_Texture = Texture::Create("assets/textures/starcraft.jpg");
		m_Texture2 = Texture::Create("assets/textures/s2.png");

		m_TextureVA = VertexArray::Create();

		float textureVertices[] {
			-1.7f, -1.0f, 0.f, 0.f, 0.f,
			 1.7f, -1.0f, 0.f, 1.f, 0.f,
			 1.7f,  1.0f, 0.f, 1.f, 1.f,
			-1.7f,  1.0f, 0.f, 0.f, 1.f,
		};
		Reference<BufferLayout> textureBufferLayout(new BufferLayout {
			{BufferLayoutDataType::Float3, "a_Position"},
			{BufferLayoutDataType::Float2, "a_TexCoord"},
		});

		Reference<VertexBuffer> textureVB = VertexBuffer::Create(textureVertices,sizeof(textureVertices),textureBufferLayout);

		m_TextureVA->AddVertexBuffer(textureVB);

		uint32_t textureIndices[] =  { 0, 1, 2, 2, 3, 0 };
		Reference<IndexBuffer> textureIB = IndexBuffer::Create(textureIndices, sizeof(textureIndices) / sizeof(uint32_t));
		m_TextureVA->SetIndexBuffer(textureIB);

		m_TextureShader = Shader::Create("assets/shaders/Texture3D.glsl");
		m_TextureShader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}
	PRINT_PROFILE();
}

void EditorApp::TestShit()
{
	using namespace Hazel;
	CLEAR_PROFILE();
	PROFILE_FPS("Frame Time");

	Renderer::Clear();

	Renderer::BeginScene(m_ViewportScene->GetComponent<SceneComponent>());
		
	m_Texture->Bind();
	Renderer::Submit(m_TextureShader, m_TextureVA);

	Renderer::EndScene();
	// ---------------------
	Renderer::BeginScene(m_Scene->GetComponent<SceneComponent>());

	m_Project.Render();

	Renderer::EndScene();
	// ---------------------
}
