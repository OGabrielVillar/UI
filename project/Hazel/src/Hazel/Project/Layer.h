#pragma once

#include "Graphics/Renderer/Framebuffer.h"

namespace Hazel
{

	class Layer 
	{
	public:
		Layer(intRect windowRect)
		  : m_Frame(windowRect),
			m_Framebuffer(nullptr)
		{}
		Layer(uint32_t width, uint32_t height, uint32_t channels)
		  : m_Frame(intRect::WH(width, height)),
			m_Framebuffer(Framebuffer::Create(width, height, channels))
		{}
		//const intRect& GetFrame() { return m_Frame; }
		vec2int GetSize() const { return m_Frame.size(); }
		int GetWidth() const { return m_Frame.width(); }
		int GetHeight() const { return m_Frame.height(); }

		const Texture& GetTexture() const;

		const void SetSize(const vec2int& size) { m_Frame.SetSize(size); }
		const void SetPosition(const vec2int& position) { m_Frame.SetPosition(position); }
		void Bind();
	private:
		intRect m_Frame;
		Ref<Framebuffer> m_Framebuffer;
	};

}
