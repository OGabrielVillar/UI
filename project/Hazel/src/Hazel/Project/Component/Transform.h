#pragma once

#include "pch.h"

namespace Hazel {

	struct TransformComponent
	{
	public:
		using vec_t = glm::vec<3,float>;
	public:
		void SetPosition(const vec_t& position);
		void SetRotation(float rotation);
		void Translate(const vec_t& translation);
		void Rotate(float rotation);
		void Scale(float scale);

		const Ref<const glm::mat4> GetMat4() const { return m_Transform; }
	private:
	Ref<glm::mat4> m_Transform = CreateReference<glm::mat4>(glm::mat4(1.f));
	vec_t m_Position = { 0.f, 0.f, 0.f};
	vec_t m_Scale = { 1.f, 1.f, 1.f};
	float m_Rotation = 0.f;
	};

}
