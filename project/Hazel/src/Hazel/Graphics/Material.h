#pragma once

namespace Hazel {

	class Material {
	public:
		Material() = default;
		Material(const vec4& color);

		inline void SetColor(const vec4& color) { m_Color = color; }

		inline const vec4& GetColor() const { return m_Color; }

	private:
		vec4 m_Color = { 0.f,0.f,0.f,0.f };
	};

}
