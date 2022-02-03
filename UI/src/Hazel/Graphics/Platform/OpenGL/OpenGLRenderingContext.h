#pragma once

#include "core.h"
#include "Graphics/Renderer/Shader.h"
#include "Graphics/Renderer/RenderingContext.h"
#include "Graphics/Renderer/VertexBuffer.h"
#include "Graphics/Renderer/IndexBuffer.h"
#include "Graphics/Renderer/VertexArray.h"

struct GLFWwindow;

namespace Hazel {

	class OpenGLRenderingContext : public RenderingContext
	{
	public:
		OpenGLRenderingContext(GLFWwindow* windowHandle);
		virtual ~OpenGLRenderingContext();
		
		virtual void Init() override;
		virtual void SwapBuffers() override;
		
		virtual void SetColor(const vec4& color) override { m_color = color; }
	private:
		GLFWwindow* m_windowHandle;
	public:
		vec4 m_color = {.99f,.8f,.85f, 1.0f};

		void InitShit();
		void TestShit();
	private:// Shit
		Reference<Shader> m_Shader;
		Reference<VertexArray> m_VertexArray;

		Reference<Shader> m_SquareShader;
		Reference<VertexArray> m_SquareVA;
	};

}
