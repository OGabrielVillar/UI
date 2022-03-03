#pragma once

namespace Hazel {

	class RenderingContext {
	public:		
		virtual ~RenderingContext() = default;
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		virtual void SetColor(const vec4&) = 0;
	};

}
