#pragma once

#include "VertexArray.h"

namespace Hazel{

	class RendererAPI {
	 public:
		enum class API {
			None = 0,
			OpenGL = 1,
		};
		using enum API;

	 public:
		virtual void Init() = 0;
		virtual void SetClearColor(const vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
		
		virtual void SetWindowSize(float width, float height) = 0;

		inline static RendererAPI::API Get() { return s_RendererAPI; }
	 private:
		static const RendererAPI::API s_RendererAPI;
	};

}
