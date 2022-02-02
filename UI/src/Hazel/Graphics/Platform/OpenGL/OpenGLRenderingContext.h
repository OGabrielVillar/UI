#pragma once

#include "core.h"
#include "Graphics/Renderer/Shader.h"
#include "../../Renderer/RenderingContext.h"
#include "../../Renderer/VertexBuffer.h"
#include "../../Renderer/IndexBuffer.h"

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
		unsigned int m_VertexArray;
		Scope<Shader> m_Shader;
		Scope<VertexBuffer> m_VertexBuffer;
		Scope<IndexBuffer> m_IndexBuffer;
	};

}
