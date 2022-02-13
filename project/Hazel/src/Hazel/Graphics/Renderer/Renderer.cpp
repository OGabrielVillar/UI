#include "pch.h"
#include "Renderer.h"

#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel 
{

	Renderer::SceneData* Renderer::s_SceneData = new SceneData();
	Reference<Shader> Renderer::s_RectShader = nullptr;
	Reference<VertexArray> Renderer::s_SquareVA = nullptr;
	Reference<Shader> Renderer::s_TextureShader = nullptr;
	
	void Renderer::Init()
	{
		RenderCommand::Init();
		InitRectDrawing();
		InitTextureDrawing();
	}
	void Renderer::InitRectDrawing()
	{
		HZ_ASSERT(s_RectShader == nullptr, "Renderer::InitRectDrawing initiating rect drawing parameters twice!");
	 // --- Rect Shader

		s_RectShader = Shader::Create("assets/shaders/Rect2D.glsl");
		
	 // --- Rect Vertex Array
		
		s_SquareVA = VertexArray::Create();

		float vertices[] {
			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
		};
		Reference<BufferLayout> buffer_layout(new BufferLayout {
			{BufferLayoutDataType::Float2, "a_Position"}
		});
		
		Reference<VertexBuffer> s_RectVB = VertexBuffer::Create(vertices, sizeof(vertices), buffer_layout);
		s_SquareVA->AddVertexBuffer(s_RectVB);

		uint32_t indices[] =  { 0, 1, 2, 2, 3, 0};
		Reference<IndexBuffer> ib = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		s_SquareVA->SetIndexBuffer(ib);
	}

	void Renderer::InitTextureDrawing()
	{
		HZ_ASSERT(s_TextureShader == nullptr, "Renderer::InitTextureDrawing initiating rect drawing parameters twice!");
	 // --- Rect Shader

		s_TextureShader = Shader::Create("assets/shaders/Texture2D.glsl");
		s_TextureShader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void Renderer::SetClearColor(const vec4& color)
	{
		RenderCommand::SetClearColor(color);
	}

	void Renderer::Clear()
	{
		RenderCommand::Clear();
	}

	void Renderer::BeginScene(Scene& scene)
	{
		scene.GetLayer().Bind();
		s_SceneData->viewProjectionMatrix = &(scene.GetCamera().GetViewProjectionMatrix());
		s_SceneData->resolution = (vec2)scene.GetLayer().GetSize();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::UnbindFramebuffers(const vec2int& resolution)
	{
		RenderCommand::UnbindFramebuffers(resolution);
	}

	void Renderer::SetWindowSize(float width, float height) 
	{
		RenderCommand::SetWindowSize(width, height);
	}

	void Renderer::Submit(const Reference<Shader>& shader, const Reference<VertexArray>& vertexArray, const mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", *(s_SceneData->viewProjectionMatrix));
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::DrawRect(const Rect& rect, const vec4& color)
	{
		s_RectShader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_RectShader)->UploadUniformFloat2("u_Resolution", s_SceneData->resolution);
		std::dynamic_pointer_cast<OpenGLShader>(s_RectShader)->UploadUniformFloat2("u_RectPosition", rect.a());
		std::dynamic_pointer_cast<OpenGLShader>(s_RectShader)->UploadUniformFloat2("u_RectSize", rect.size());
		std::dynamic_pointer_cast<OpenGLShader>(s_RectShader)->UploadUniformFloat4("u_Color", color);
		s_SquareVA->Bind();
		RenderCommand::DrawIndexed(s_SquareVA);
	}

	void Renderer::DrawTexture(const Rect& rect, const Texture& texture)
	{
		s_TextureShader->Bind();
		texture.Bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_TextureShader)->UploadUniformFloat2("u_Resolution", s_SceneData->resolution);
		std::dynamic_pointer_cast<OpenGLShader>(s_TextureShader)->UploadUniformFloat2("u_RectPosition", rect.a());
		std::dynamic_pointer_cast<OpenGLShader>(s_TextureShader)->UploadUniformFloat2("u_RectSize", rect.size());
		s_SquareVA->Bind();
		RenderCommand::DrawIndexed(s_SquareVA);
	}

	/*void DrawString(const std::string& string, const Reference<Font>& font, const glm::mat4& transform, float maxWidth, const glm::vec4& color, float lineHeightOffset, float kerningOffset)
	{
		if (string.empty())
			return;

		float textureIndex = 0.0f;

		// TODO(Yan): this isn't really ideal, but we need to iterate through UTF-8 code points
		std::u32string utf32string = To_UTF32(string);

		Ref<Texture2D> fontAtlas = font->GetFontAtlas();
		HZ_CORE_ASSERT(fontAtlas);

		for (uint32_t i = 0; i < m_FontTextureSlotIndex; i++)
		{
			if (*m_FontTextureSlots[i].Raw() == *fontAtlas.Raw())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)m_FontTextureSlotIndex;
			m_FontTextureSlots[m_FontTextureSlotIndex] = fontAtlas;
			m_FontTextureSlotIndex++;
		}

		auto& fontGeometry = font->GetMSDFData()->FontGeometry;
		const auto& metrics = fontGeometry.getMetrics();

		// TODO(Yan): these font metrics really should be cleaned up/refactored...
		//            (this is a first pass WIP)
		std::vector<int> nextLines;
		{
			double x = 0.0;
			double fsScale = 1 / (metrics.ascenderY - metrics.descenderY);
			double y = -fsScale * metrics.ascenderY;
			int lastSpace = -1;
			for (int i = 0; i < utf32string.size(); i++)
			{
				char32_t character = utf32string[i];
				if (character == '\n')
				{
					x = 0;
					y -= fsScale * metrics.lineHeight + lineHeightOffset;
					continue;
				}

				auto glyph = fontGeometry.getGlyph(character);
				if (!glyph)
					glyph = fontGeometry.getGlyph('?');
				if (!glyph)
					continue;

				if (character != ' ')
				{
					// Calc geo
					double pl, pb, pr, pt;
					glyph->getQuadPlaneBounds(pl, pb, pr, pt);
					glm::vec2 quadMin((float)pl, (float)pb);
					glm::vec2 quadMax((float)pr, (float)pt);

					quadMin *= fsScale;
					quadMax *= fsScale;
					quadMin += glm::vec2(x, y);
					quadMax += glm::vec2(x, y);

					if (quadMax.x > maxWidth && lastSpace != -1)
					{
						i = lastSpace;
						nextLines.emplace_back(lastSpace);
						lastSpace = -1;
						x = 0;
						y -= fsScale * metrics.lineHeight + lineHeightOffset;
					}
				}
				else
				{
					lastSpace = i;
				}

				double advance = glyph->getAdvance();
				fontGeometry.getAdvance(advance, character, utf32string[i + 1]);
				x += fsScale * advance + kerningOffset;
			}
		}

		{
			double x = 0.0;
			double fsScale = 1 / (metrics.ascenderY - metrics.descenderY);
			double y = 0.0;// -fsScale * metrics.ascenderY;
			for (int i = 0; i < utf32string.size(); i++)
			{
				char32_t character = utf32string[i];
				if (character == '\n' || NextLine(i, nextLines))
				{
					x = 0;
					y -= fsScale * metrics.lineHeight + lineHeightOffset;
					continue;
				}

				auto glyph = fontGeometry.getGlyph(character);
				if (!glyph)
					glyph = fontGeometry.getGlyph('?');
				if (!glyph)
					continue;

				double l, b, r, t;
				glyph->getQuadAtlasBounds(l, b, r, t);

				double pl, pb, pr, pt;
				glyph->getQuadPlaneBounds(pl, pb, pr, pt);

				pl *= fsScale, pb *= fsScale, pr *= fsScale, pt *= fsScale;
				pl += x, pb += y, pr += x, pt += y;

				double texelWidth = 1. / fontAtlas->GetWidth();
				double texelHeight = 1. / fontAtlas->GetHeight();
				l *= texelWidth, b *= texelHeight, r *= texelWidth, t *= texelHeight;

				// ImGui::Begin("Font");
				// ImGui::Text("Size: %d, %d", m_ExampleFontSheet->GetWidth(), m_ExampleFontSheet->GetHeight());
				// UI::Image(m_ExampleFontSheet, ImVec2(m_ExampleFontSheet->GetWidth(), m_ExampleFontSheet->GetHeight()), ImVec2(0, 1), ImVec2(1, 0));
				// ImGui::End();

				m_TextVertexBufferPtr->Position = transform * glm::vec4(pl, pb, 0.0f, 1.0f);
				m_TextVertexBufferPtr->Color = color;
				m_TextVertexBufferPtr->TexCoord = { l, b };
				m_TextVertexBufferPtr->TexIndex = textureIndex;
				m_TextVertexBufferPtr++;

				m_TextVertexBufferPtr->Position = transform * glm::vec4(pl, pt, 0.0f, 1.0f);
				m_TextVertexBufferPtr->Color = color;
				m_TextVertexBufferPtr->TexCoord = { l, t };
				m_TextVertexBufferPtr->TexIndex = textureIndex;
				m_TextVertexBufferPtr++;

				m_TextVertexBufferPtr->Position = transform * glm::vec4(pr, pt, 0.0f, 1.0f);
				m_TextVertexBufferPtr->Color = color;
				m_TextVertexBufferPtr->TexCoord = { r, t };
				m_TextVertexBufferPtr->TexIndex = textureIndex;
				m_TextVertexBufferPtr++;

				m_TextVertexBufferPtr->Position = transform * glm::vec4(pr, pb, 0.0f, 1.0f);
				m_TextVertexBufferPtr->Color = color;
				m_TextVertexBufferPtr->TexCoord = { r, b };
				m_TextVertexBufferPtr->TexIndex = textureIndex;
				m_TextVertexBufferPtr++;

				m_TextIndexCount += 6;

				double advance = glyph->getAdvance();
				fontGeometry.getAdvance(advance, character, utf32string[i + 1]);
				x += fsScale * advance + kerningOffset;

				m_Stats.QuadCount++;
			}
		}

	}*/
}
