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
	for (auto& command : m_Commands) {
		if (command.Handle(event))
			return true;
	}
	return false;
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

	// Commands:
	{ // 
		
		m_Commands.push_back(Command());
		m_Commands.back().SetFunction([this]() 
		{
			m_Texture->SetInterpolation(m_Interpolation[m_InterpolationIndex]);
			m_InterpolationIndex++;
			m_InterpolationIndex %= 2;
			return true;
		});
		m_Commands.back().AddTrigger(EventKeyboardKey(Keyboard::Key::F9, Keyboard::Action::Release));
		
		
		m_Commands.push_back(Command());
		m_Commands.back().SetFunction<EventCursorPosition>([this](const EventCursorPosition* event) 
		{
			m_TexturePosition = event->position;
			return true;
		});
		m_Commands.back().AddTrigger(EventCursorPosition());


		m_Commands.push_back(Command());
		m_Commands.back().SetFunction<EventMouseScroll>([this](const EventMouseScroll* event) 
		{
			m_ViewportCamera->GetTransform().Scale(1.f - (0.1f * event->offset.y));
			return true;
		});
		m_Commands.back().AddTrigger(EventMouseScroll());


		m_Commands.push_back(Command());
		m_Commands.back().SetFunction<EventWindowSize>([this](const EventWindowSize* event) 
		{
			vec2 resolution = (vec2)event->size;
			vec2 aspectRatio (resolution / resolution.y);
			m_Camera->SetAspectRatio(aspectRatio);
			return true;
		});
		m_Commands.back().AddTrigger(EventWindowSize());
	}

	// --- Project Initialization
	m_Camera = m_Project.CreateCamera({1.f,1.f});
	m_Scene.SetCamera(m_Camera);

	m_ViewportCamera = m_Project.CreateCamera({1.f,1.f});
	m_ViewportScene.SetCamera(m_ViewportCamera);

	// --- Renderer Initialization
	vec2 resolution = (vec2)m_Window.get()->GetResolution();
	vec2 aspectRatio (resolution / resolution.y);
	m_Camera->SetAspectRatio(aspectRatio);

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

	// --- Triangle

	m_VertexArray = VertexArray::Create();

	float vertices[] {
		-0.5f, -0.2f, 0.0f , 1.f, 0.f, 1.f, 1.f,
		 0.5f, -0.2f, 0.0f , 1.f, 1.f, 0.f, 1.f,
		 0.0f, -1.0f, 0.0f , 0.f, 1.f, 1.f, 1.f,
	};
	Reference<BufferLayout> buffer_layout(new BufferLayout {
		{BufferLayoutDataType::Float3, "a_Position"},
		{BufferLayoutDataType::Float4, "a_Color"   },
	});
		
	Reference<VertexBuffer> m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices), buffer_layout);
	
	m_VertexArray->AddVertexBuffer(m_VertexBuffer);

	uint32_t indices[] =  { 0, 1, 2 };
	Reference<IndexBuffer> m_IndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	m_VertexArray->SetIndexBuffer(m_IndexBuffer);
		
	string vertexSrc = R"(
		#version 330 core
		
		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;
			
		uniform mat4 u_ViewProjection;
		uniform mat4 u_Transform;

		out vec4 v_Color;

		void main()
		{
			v_Color = a_Color;
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
		}
	)";
		
	string fragmentSrc = R"(
		#version 330 core
		
		layout(location = 0) out vec4 color;

		in vec4 v_Color;

		void main()
		{
			color = v_Color;
		}
	)";

	m_Shader = Shader::Create("Triangle", vertexSrc, fragmentSrc);

}

void EditorApp::TestShit()
{
	using namespace Hazel;

	Renderer::Clear();

	Renderer::BeginScene(m_ViewportScene);
		
	m_Texture->Bind();
	Renderer::Submit(m_TextureShader, m_TextureVA);

	Renderer::Submit(m_Shader, m_VertexArray);

	Renderer::EndScene();
	// ---------------------
	Renderer::BeginScene(m_Scene);

	//Renderer::DrawRect(m_Rect, m_RectColor);
	
	Renderer::DrawTexture(Rect::XYWH(m_TexturePosition, m_TextureSize), m_ViewportScene.GetLayer().GetTexture());
	//Renderer::DrawTexture(Rect::XYWH(m_TexturePosition, m_TextureSize), *m_Texture);
	
	Renderer::DrawTexture(m_Rect, m_ViewportScene.GetLayer().GetTexture());

	Renderer::EndScene();
	// ---------------------
}
