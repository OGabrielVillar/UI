#pragma once

#include "RendererAPI.h"
#include "VertexArray.h"

namespace Hazel {

	class RenderCommand {
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}
		inline static void SetClearColor(const vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}

		inline static void SetWindowSize(float width, float height)
		{
			s_RendererAPI->SetWindowSize(width, height);
		}

	private:
		static RendererAPI* s_RendererAPI;
	};

}
