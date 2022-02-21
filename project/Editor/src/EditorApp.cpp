#include <Hazel.h>

#include "EditorApp.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Project/Component/CommandCardComponent.h"

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

	// --- Aspect Ratio
	vec2 resolution = (vec2)m_Window.get()->GetResolution();
	vec2 aspectRatio (resolution / resolution.y);

	vec2 viewportResolution = m_Rect.size();
	vec2 viewportAspectRatio (viewportResolution / viewportResolution.y);
	m_Viewport.SetSize((vec2int)m_Rect.size());

	// --- Project Initialization
	m_Camera = m_Project.CreateCamera(aspectRatio);
	m_Scene.SetCamera(m_Camera);

	m_ViewportCamera = m_Project.CreateCamera({viewportAspectRatio});
	m_ViewportScene.SetCamera(m_ViewportCamera);

	auto commandCardEntity = m_Project.CreateEntity("Command Card");
	auto commandCard = commandCardEntity.AddComponent<CommandCardComponent>();

	// Commands:
	{
		
		auto cmd = commandCard->AddCommand();
		cmd->SetFunction([this]() 
		{
			m_Texture->SetInterpolation(m_Interpolation[m_InterpolationIndex]);
			m_InterpolationIndex++;
			m_InterpolationIndex %= 2;
			return true;
		});
		cmd->AddTrigger(EventKeyboardKey(Keyboard::Key::F9, Keyboard::Action::Release));
		
		
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

void EditorApp::TestShit()
{
	using namespace Hazel;

	Renderer::Clear();

	Renderer::BeginScene(m_ViewportScene);
		
	m_Texture->Bind();
	Renderer::Submit(m_TextureShader, m_TextureVA);

	Renderer::EndScene();
	// ---------------------
	Renderer::BeginScene(m_Scene);

	//Renderer::DrawRect(m_Rect, m_RectColor);
	
	//Renderer::DrawTexture(Rect::XYWH(m_TexturePosition, m_TextureSize), m_ViewportScene.GetCanvas().GetTexture());
	//Renderer::DrawTexture(Rect::XYWH(m_TexturePosition, m_TextureSize), *m_Texture);
	
	Renderer::DrawTexture(m_Rect, m_ViewportScene.GetCanvas().GetTexture());

	Renderer::EndScene();
	// ---------------------
}
