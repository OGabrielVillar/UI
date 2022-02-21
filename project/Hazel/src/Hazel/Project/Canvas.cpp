#include "pch.h"
#include "Canvas.h"

#include "Graphics/Renderer/Renderer.h"

namespace Hazel {
	const Texture& Canvas::GetTexture() const
	{ 
		HZ_ASSERT(m_Framebuffer, "Canvas::GetTexture: There is no framebuffer initialized in this Canvas!");
		return m_Framebuffer->GetTexture(); 
	}
	void Canvas::Bind()
    {
		if (m_Framebuffer) {
			m_Framebuffer->Bind();
			Renderer::Clear();
		}
		else
			Renderer::UnbindFramebuffers(m_Frame.size());
    }

}
