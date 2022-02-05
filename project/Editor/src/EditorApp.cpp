#include <Hazel.h>
#include <Hazel/Run/Entry.h>

class EditorApp : public Hazel::Application {
 public:
	EditorApp(const std::string& name, Hazel::Window::Flags flags) 
		: Application(name, flags)
	{}
	virtual ~EditorApp() = default;

	virtual void OnInit() override
	{
		InitShit();
	}
	
	virtual bool OnEvent(const Hazel::Event& event) override
	{
		for (auto& command : m_Commands) {
			if (command.Handle(event))
				return true;
		}
		return false;
	}

	virtual void OnShutdown() override {}

	virtual void OnUpdate() override
	{
		TestShit();
	}

	void InitShit()
	{
		using namespace Hazel;

	 // Commands:
		{ // 
			m_Commands.push_back(Command("RightGo", KeyboardKeyEvent(Keyboard::Key::Right,Keyboard::Action::Press)));
			m_Commands.back().SetFunction<KeyboardKeyEvent>([this](const KeyboardKeyEvent* event) { 
				cameraVelocity.x = velocity;
				return true; 
			});

			m_Commands.push_back(Command("RightStop", KeyboardKeyEvent(Keyboard::Key::Right,Keyboard::Action::Release)));
			m_Commands.back().SetFunction<KeyboardKeyEvent>([this](const KeyboardKeyEvent* event) { 
				cameraVelocity.x = 0.f;
				return true; 
			});

			m_Commands.push_back(Command("LeftGo", KeyboardKeyEvent(Keyboard::Key::Left,Keyboard::Action::Press)));
			m_Commands.back().SetFunction<KeyboardKeyEvent>([this](const KeyboardKeyEvent* event) { 
				cameraVelocity.x = -velocity;
				return true; 
			});

			m_Commands.push_back(Command("LeftStop", KeyboardKeyEvent(Keyboard::Key::Left,Keyboard::Action::Release)));
			m_Commands.back().SetFunction<KeyboardKeyEvent>([this](const KeyboardKeyEvent* event) { 
				cameraVelocity.x = 0.f;
				return true; 
			});
			
			m_Commands.push_back(Command("UpGo", KeyboardKeyEvent(Keyboard::Key::Up,Keyboard::Action::Press)));
			m_Commands.back().SetFunction<KeyboardKeyEvent>([this](const KeyboardKeyEvent* event) { 
				cameraVelocity.y = velocity;
				return true; 
			});

			m_Commands.push_back(Command("UpStop", KeyboardKeyEvent(Keyboard::Key::Up,Keyboard::Action::Release)));
			m_Commands.back().SetFunction<KeyboardKeyEvent>([this](const KeyboardKeyEvent* event) { 
				cameraVelocity.y = 0.f;
				return true; 
			});

			m_Commands.push_back(Command("DownGo", KeyboardKeyEvent(Keyboard::Key::Down,Keyboard::Action::Press)));
			m_Commands.back().SetFunction<KeyboardKeyEvent>([this](const KeyboardKeyEvent* event) { 
				cameraVelocity.y = -velocity;
				return true; 
			});

			m_Commands.push_back(Command("DownStop", KeyboardKeyEvent(Keyboard::Key::Down,Keyboard::Action::Release)));
			m_Commands.back().SetFunction<KeyboardKeyEvent>([this](const KeyboardKeyEvent* event) { 
				cameraVelocity.y = 0.f;
				return true; 
			});
		}
	 // Init Renderer

		Renderer::Init();
		Renderer::SetClearColor(vec4{ 0.05f, 0.05f, 0.05f, .95f });

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

			out vec4 v_Color;

			void main()
			{
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_Shader = CreateReference<Shader>(vertexSrc, fragmentSrc);


	 // --- Square
		m_SquareVA = VertexArray::Create();

		float squareVertices[] {
			 -0.8f, -0.8f, 0.0f,
			 -0.8f,  0.8f, 0.0f,
			  0.8f,  0.8f, 0.0f,
			  0.8f, -0.8f, 0.0f,
		};
		Reference<BufferLayout> squareBufferLayout(new BufferLayout {
			{BufferLayoutDataType::Float3, "a_Position"},
		});

		Reference<VertexBuffer> squareVB = VertexBuffer::Create(squareVertices,sizeof(squareVertices),squareBufferLayout);

		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[] =  { 0, 1, 2, 2, 3, 0 };
		Reference<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(squareIB);

		string vertexSrc_square = R"(
			#version 330 core
		
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";
		
		string fragmentSrc_square = R"(
			#version 330 core
		
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";
				//color = vec4(v_Position * 0.5 + 0.5, 1.0);

		m_SquareShader = CreateReference<Shader>(vertexSrc_square, fragmentSrc_square);
	}

	void TestShit()
	{
		using namespace Hazel;

		m_Camera.MoveBy(cameraVelocity * m_dt);
		
		Renderer::Clear();

		Renderer::BeginScene(m_Camera);
		
		Renderer::Submit(m_SquareShader, m_SquareVA);

		Renderer::Submit(m_Shader, m_VertexArray);

		Renderer::DrawRect(m_Rect, m_RectColor);

		Renderer::EndScene();
	}

private:// Shit
	float velocity = 1.f;
	glm::vec2 cameraVelocity = { 0.f, 0.f };

	Hazel::Reference<Hazel::Shader> m_Shader;
	Hazel::Reference<Hazel::VertexArray> m_VertexArray;

	Hazel::Reference<Hazel::Shader> m_SquareShader;
	Hazel::Reference<Hazel::VertexArray> m_SquareVA;

	Hazel::Rect m_Rect = Hazel::Rect::LTRB(50.f,50.f,370.f,170.f);
	Hazel::vec4 m_RectColor = { 0.9f, 0.75f, 0.8f, 1.f };

	Hazel::Camera m_Camera = Hazel::Rect(-1.777777777f, 1.777777777f, 1.f, -1.f);
	float rotation_mod = 1.f;

	std::vector<Hazel::Command> m_Commands;

};

Hazel::Application* Hazel::CreateApplication()
{

	return new EditorApp("Hazel Editor", Window::Flag::Transparent | Window::Flag::Focused);

}
