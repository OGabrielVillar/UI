#include "pch.h"
#include "Renderer.h"

#include "RenderCommand.h"

namespace Hazel 
{

	Renderer::SceneData* Renderer::s_SceneData = new SceneData();
	Reference<Shader> Renderer::s_RectShader = nullptr;
	Reference<VertexArray> Renderer::s_RectVA = nullptr;
	Reference<VertexBuffer> Renderer::s_RectVB = nullptr;
	
	void Renderer::Init()
	{
		InitRectDrawing();
	}
	void Renderer::InitRectDrawing()
	{
		HZ_ASSERT(s_RectShader == nullptr, "Renderer::InitRectDrawing initiating rect drawing parameters twice!");
	 // --- Rect Shader
		const string vertexSrc = R"(
			#version 330 core
		
			layout(location = 0) in vec2 a_Position;

			uniform mat4 u_Projection;
			uniform vec4 u_Color;
			
			out vec4 v_Color;

			void main()
			{
				v_Color = u_Color;
				gl_Position = u_Projection * vec4(a_Position, 0.0, 1.0);
			}
		)";
		
		const string fragmentSrc = R"(
			#version 330 core
		
			layout(location = 0) out vec4 color;

			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Color.x, v_Color.y, v_Color.z, 1.0);
			}
		)";

		s_RectShader = std::make_shared<Shader>(vertexSrc, fragmentSrc);
		
	 // --- Rect Vertex Array
		
		s_RectVA = VertexArray::Create();

		float vertices[] {
			 0.0f, 0.0f,
			 0.0f, 0.0f,
			 0.0f, 0.0f,
			 0.0f, 0.0f,
		};
		Reference<BufferLayout> buffer_layout(new BufferLayout {
			{BufferLayoutDataType::Float2, "a_Position"},
		});
		
		s_RectVB = VertexBuffer::Create(vertices, sizeof(vertices), buffer_layout);
		s_RectVA->AddVertexBuffer(s_RectVB);

		uint32_t indices[] =  { 0, 1, 2, 2, 3, 0};
		Reference<IndexBuffer> ib = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		s_RectVA->SetIndexBuffer(ib);
	}

	void Renderer::SetClearColor(const vec4& color)
	{
		RenderCommand::SetClearColor(color);
	}

	void Renderer::Clear()
	{
		RenderCommand::Clear();
	}

	void Renderer::BeginScene(Camera& camera)
	{
		s_SceneData->viewProjectionMatrix = &camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::SetWindowSize(float width, float height) 
	{
		s_SceneData->windowMatrix = glm::ortho(0.f, width, height, 0.f, -1.f, 1.f);
		RenderCommand::SetWindowSize(width, height);
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUniform("u_ViewProjection", *(s_SceneData->viewProjectionMatrix));
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::DrawRect(const Rect& rect, const vec4& color)
	{
		float vertices[] {
			 rect.l, rect.t,
			 rect.l, rect.b,
			 rect.r, rect.b,
			 rect.r, rect.t
		};
		s_RectVA->GetVertexBuffers()[0]->ChangeBufferData(vertices,sizeof(vertices));
		// --- Submit
		s_RectShader->Bind();
		s_RectShader->UploadUniform("u_Projection", s_SceneData->windowMatrix);
		s_RectShader->UploadUniform("u_Color", color);
		s_RectVA->Bind();
		RenderCommand::DrawIndexed(s_RectVA);
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
