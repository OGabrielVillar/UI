#pragma once

#include "Graphics/RenderingContext.h"

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
	};

}
