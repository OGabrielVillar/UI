#pragma once

#include "Graphics/Renderer/RendererAPI.h"

namespace Hazel 
{

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
		
		virtual void SetWindowSize(float width, float height) override;
	private:
		vec4 m_ClearColor;
	};

}

