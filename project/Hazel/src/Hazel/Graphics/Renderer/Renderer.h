#pragma once

#include "VertexArray.h"
#include "Shader.h"
#include "Project/Scene.h"
#include "Graphics/Texture.h"

//#include <glm/gtc/matrix_transform.hpp>

namespace Hazel {

	using Geometry::intRect;

	class Renderer {
	 public:
		static void Init();

		static void InitRectDrawing();
		static void InitTextureDrawing();

		static void SetClearColor(const vec4& color);
		static void Clear();

		static void BeginScene(Scene& scene);
		static void EndScene();
		static void UnbindFramebuffers(const vec2int& resolution);
		
		static void SetWindowSize(float width, float height);

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const mat4& transform = mat4(1.f));
		static void DrawRect(const Rect& rect, const vec4& color);
		static void DrawLine(const vec2& rect, const vec4& color);
		static void DrawCircle(const Circle& rect, const vec4& color);
		static void DrawTexture(const Rect& rect, const Texture& texture);
		/*static void DrawString(
			const std::string& string, 
			const Reference<Font>& font, 
			const glm::mat4& transform, 
			float maxWidth, 
			const glm::vec4& color, 
			float lineHeightOffset, 
			float kerningOffset
		);*/

	 private:
		struct SceneData {
			glm::vec2 resolution;
			const glm::mat4* viewProjectionMatrix;
		};
		static SceneData* s_SceneData;

	 private:
		static Reference<VertexArray> s_SquareVA;
		static Reference<Shader> s_RectShader;
		static Reference<Shader> s_TextureShader;

	};

}
