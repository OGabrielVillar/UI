#include "pch.h"
#include "Transform.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Hazel {

	void Transform::SetPosition(const vec_t& position)
	{
		*m_Transform = glm::translate(*m_Transform, position - m_Position);
		m_Position = position;
	}

	void Transform::SetRotation(float rotation)
	{
		*m_Transform = glm::rotate(*m_Transform, rotation - m_Rotation, { 0.f,0.f,1.f });
		m_Rotation = rotation;
	}

	void Transform::Translate(const vec_t& translation)
	{
		*m_Transform = glm::translate(*m_Transform, translation);
		m_Position += translation;
	}

	void Transform::Rotate(float rotation)
	{
		*m_Transform = glm::rotate(*m_Transform, rotation, { 0.f,0.f,1.f });
		m_Rotation += rotation;
	}

	void Transform::Scale(float scale)
	{
		*m_Transform = glm::scale(*m_Transform, { scale,scale,scale });
		m_Scale *= scale;
	}

}
