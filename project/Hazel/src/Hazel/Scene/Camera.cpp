#include "pch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Hazel {

	Hazel::Camera::Camera(const Rect& rect)
	  : m_Projection(glm::ortho(rect.left, rect.right, rect.bottom, rect.top, -1.f, 1.f)),
		m_View(1.f)
	{
		m_ViewProjection = m_Projection * m_View;
	}

	const mat4& Camera::GetViewProjectionMatrix()
	{
		if (m_ViewHadChanged)
			RecalculateView();
		return m_ViewProjection; 
	}

	void Camera::RecalculateView()
	{
		mat4 transform = glm::translate(mat4(1.f), m_Position)
			* glm::rotate(mat4(1.f), m_Rotation, vec3(0.f,0.f,1.f));

		m_View = glm::inverse(transform);

		m_ViewProjection = m_Projection * m_View;
	}

}
