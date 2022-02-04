#include "pch.h"

#include "Application.h"
#include "Log.h"
#include "Graphics/Renderer/Renderer.h"

namespace Hazel 
{
	Application::Application()
	{
		Init();
	}
	Application::~Application()
	{
		glfwTerminate();
	}

	void Application::Init()
	{
		HZ_APP_TRACE("Initializing ... ");

		m_Window = CreateReference<Window>("Hazel");
		m_Window->Init();

		InitShit();
		
		m_dt = m_dt_timer.update().count();
	}

	void Application::Run()
	{
		HZ_APP_TRACE("Start running ... ");

	 // Loop until the user closes the window
		while (m_Window->IsAlive()) {
			m_dt = m_dt_timer.update().count();
			
			m_Window->Run();

			TestShit();
		}
		HZ_APP_TRACE(" ... Stop running!");
	}

	void Application::InitShit()
	{
		Renderer::Init();
		Renderer::SetClearColor(vec4{0.05f,0.05f,0.05f, .95f});

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

	void Application::TestShit()
	{
		Renderer::Clear();

		Renderer::BeginScene(m_Camera);
		
		m_Camera.RotateBy(0.1f*m_dt);

		Renderer::Submit(m_SquareShader, m_SquareVA);

		Renderer::Submit(m_Shader, m_VertexArray);

		Renderer::DrawRect(m_Rect, m_RectColor);

		Renderer::EndScene();
	}

}
