#include "pch.h"
#include "OpenGLRenderingContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../../Renderer/BufferLayout.h"
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

	static GLenum ToOpenGLBaseType(BufferLayoutDataType type) {
		switch (type)
		{
		case Hazel::BufferLayoutDataType::Bool:		  return GL_BOOL;
		case Hazel::BufferLayoutDataType::Float:	  return GL_FLOAT;
		case Hazel::BufferLayoutDataType::Float2:	  return GL_FLOAT;
		case Hazel::BufferLayoutDataType::Float3:	  return GL_FLOAT;
		case Hazel::BufferLayoutDataType::Float4:	  return GL_FLOAT;
		case Hazel::BufferLayoutDataType::Int:		  return GL_INT;
		case Hazel::BufferLayoutDataType::Int2:		  return GL_INT;
		case Hazel::BufferLayoutDataType::Int3:		  return GL_INT;
		case Hazel::BufferLayoutDataType::Int4:		  return GL_INT;
		case Hazel::BufferLayoutDataType::Mat3:		  return GL_FLOAT;
		case Hazel::BufferLayoutDataType::Mat4:		  return GL_FLOAT;
		}
		HZ_ASSERT(false,"[Hazel::ToOpenGLBaseType] Unsupported \"BufferLayoutDataType\" case!")
	}

	void OpenGLRenderingContext::InitShit()
	{
		glGenVertexArrays(1 , &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[] {
			 -0.5f, -0.5f, 0.0f , 1.f, 0.f, 1.f, 1.f,
			  0.5f, -0.5f, 0.0f , 1.f, 1.f, 0.f, 1.f,
			  0.0f,  0.5f, 0.0f , 0.f, 1.f, 1.f, 1.f,
		};
		m_VertexBuffer.reset(VertexBuffer::Create(vertices,sizeof(vertices)));
		
		BufferLayout buffer_layout {
			{ BufferLayoutDataType::Float3, "a_Position" },
			{ BufferLayoutDataType::Float4, "a_Color"    },
			//{ BufferLayoutDataType::Float3, "a_Normal"   },
		};
	
		uint32_t index = 0;
		for (auto& element : buffer_layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, 
				element.Count, 
				ToOpenGLBaseType(element.Type), 
				element.Normalized ? GL_FALSE : GL_TRUE, 
				buffer_layout.GetStride(), 
				(const void*)element.Offset);
			index++;
		}

		uint32_t indices[] =  { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

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
				//color = vec4(v_Position * 0.5 + 0.5, 1.0);

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	void OpenGLRenderingContext::TestShit()
	{
		m_Shader->Bind();
		glBindVertexArray(m_VertexArray);
		glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}
