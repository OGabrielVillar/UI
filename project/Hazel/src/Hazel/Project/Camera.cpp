#include "pch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Hazel {

	Camera2::Camera2(const vec2& aspectRatio, const Ref<const mat4> transform)
	  : m_Projection(glm::ortho(-aspectRatio.x / 2.f, aspectRatio.x / 2.f, -aspectRatio.y / 2.f, aspectRatio.y / 2.f, -1.f, 1.f)),
		m_View(1.f),
		m_Transform(transform)
	{
		m_ViewProjection = m_Projection * m_View;
	}

	void Camera2::SetAspectRatio(const vec2& aspectRatio)
	{
		m_Projection = glm::ortho(-aspectRatio.x / 2.f, aspectRatio.x / 2.f, -aspectRatio.y / 2.f, aspectRatio.y / 2.f, -1.f, 1.f);
	}

	const mat4& Camera2::GetViewProjectionMatrix()
	{
		RecalculateView();
		return m_ViewProjection; 
	}

	void Camera2::RecalculateView()
	{
		m_View = glm::inverse(*m_Transform);
		m_ViewProjection = m_Projection * m_View;
	}

}
