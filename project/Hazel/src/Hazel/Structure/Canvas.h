#pragma once

#include "Graphics/Framebuffer.h"
#include "UI/Layout.h"

namespace Hazel
{

	class Canvas 
	{
	public:
		Canvas(const intRect& windowRect)
		  : m_Rect(windowRect),
			m_Framebuffer(nullptr)
		{}
		Canvas(int width, int height, uint32_t channels)
		  : m_Rect(intRect::WH(width, height)),
			m_Framebuffer(Framebuffer::Create((uint32_t)width, (uint32_t)height, channels))
		{}
		//const intRect& GetFrame() { return m_Frame; }
		const vec2int& GetSize() const { return m_Rect.size(); }
		const vec2int& GetPosition() const { return m_Rect.a(); }
		int GetWidth() const { return m_Rect.width(); }
		int GetHeight() const { return m_Rect.height(); }
		const intRect& GetLayout() const { return m_Rect; }

		const Texture& GetTexture() const;

		const void SetSize(const vec2int& size) { 
			m_Rect.SetSize(size); 
			if (m_Framebuffer != nullptr)
				m_Framebuffer->Resize(size); 
		}
		const void SetPosition(const vec2int& position) { m_Rect.SetPosition(position); }
		void Bind();
	private:
		intRect m_Rect;
		Ref<Framebuffer> m_Framebuffer = nullptr;
	};

}
