#pragma once

#include "VertexArray.h"
#include "Shader.h"
#include "Scene/Camera.h"

//#include <glm/gtc/matrix_transform.hpp>

namespace Hazel {

	using Geometry::intRect;

	class Renderer {
	 public:
		static void Init();

		static void InitRectDrawing();

		static void SetClearColor(const vec4& color);
		static void Clear();

		static void BeginScene(Camera& camera);
		static void EndScene();
		
		static void SetWindowSize(float width, float height);

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
		static void DrawRect(const Rect& rect, const vec4& color);
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
		static Shader* GenerateSolidShader();

		struct SceneData {
			glm::mat4 windowMatrix;
			const glm::mat4* viewProjectionMatrix;
		};
		static SceneData* s_SceneData;

	 private:
		static Reference<Shader> s_RectShader;
		static Reference<VertexArray> s_RectVA;
		static Reference<VertexBuffer> s_RectVB;

	};

}
