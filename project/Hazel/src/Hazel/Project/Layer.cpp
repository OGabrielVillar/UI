#include "pch.h"
#include "Layer.h"

#include "Graphics/Renderer/Renderer.h"

namespace Hazel {
	const Texture& Layer::GetTexture() const
	{ 
		HZ_ASSERT(m_Framebuffer, "Layer::GetTexture: There is no framebuffer initialized in this layer!");
		return m_Framebuffer->GetTexture(); 
	}
	void Layer::Bind()
    {
		if (m_Framebuffer) {
			m_Framebuffer->Bind();
			Renderer::Clear();
		}
		else
			Renderer::UnbindFramebuffers(m_Frame.size());
    }

}
