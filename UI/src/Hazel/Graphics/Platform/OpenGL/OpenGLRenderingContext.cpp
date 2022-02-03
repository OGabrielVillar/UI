#include "pch.h"
#include "OpenGLRenderingContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Graphics/Renderer/BufferLayout.h"
#include "Run/Log.h"

namespace Hazel {

	OpenGLRenderingContext::OpenGLRenderingContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)
	{
		HZ_ASSERT(windowHandle,"OpenGLRenderingContext: Window handle is null!");
	}

	OpenGLRenderingContext::~OpenGLRenderingContext()
	{}

	void OpenGLRenderingContext::Init()
	{
		// Make the window's context current
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_ASSERT(status,"OpenGLRenderingContext: Failed to load Glad!");
		
		HZ_WIN_TRACE("Vendor: {}", glGetString(GL_VENDOR));
		HZ_WIN_TRACE("Renderer: {}", glGetString(GL_RENDERER));
		HZ_WIN_TRACE("Version: {}", glGetString(GL_VERSION));

		InitShit();

	}

	void OpenGLRenderingContext::SwapBuffers() 
	{
		//glClearColor(m_color.r,m_color.g,m_color.b, .5f);
		glClearColor(0.05f,0.05f,0.05f, .95f);

		glClear(GL_COLOR_BUFFER_BIT);

		TestShit();

		glfwSwapBuffers(m_windowHandle);
	}

	void OpenGLRenderingContext::InitShit()
	{
	 // --- Triangle
		m_VertexArray = VertexArray::Create();

		float vertices[] {
			 -0.5f,  0.0f, 0.0f , 1.f, 0.f, 1.f, 1.f,
			  0.5f,  0.0f, 0.0f , 1.f, 1.f, 0.f, 1.f,
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

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";
		
		string fragmentSrc = R"(
			#version 330 core
		
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
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
			 -1.0f, -1.0f, 0.0f,
			 -1.0f,  1.0f, 0.0f,
			  1.0f,  1.0f, 0.0f,
			  1.0f, -1.0f, 0.0f,
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

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
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

	void OpenGLRenderingContext::TestShit()
	{
		m_SquareShader->Bind();
		m_SquareVA->Bind();
		glDrawElements(GL_TRIANGLES, m_SquareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

		m_Shader->Bind();
		m_VertexArray->Bind();
		glDrawElements(GL_TRIANGLES,  m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}
