#pragma once

#include "Core/Geometry/Rect.h"
#include "Core/Geometry/Angle.h"


namespace Hazel 
{
	using Geometry::Rect;
	using Geometry::angle;
	
	using glm::mat4;
	using glm::vec3;

	class Camera {
	public:
		Camera(const Rect& rect);

		void SetPosition(const vec3& position) { m_Position = position; m_ViewHadChanged = true; }
		void SetRotation(float rotation) { m_Rotation = rotation; m_ViewHadChanged = true; }
		void RotateBy(float rotation) { m_Rotation += rotation; m_ViewHadChanged = true; }

		const vec3& GetPosition() const { return m_Position; }
		float GetRotation() const { return m_Rotation; }

		const mat4& GetViewMatrix(){
			if (m_ViewHadChanged)
				RecalculateView();
			return m_View; 
		}
		const mat4& GetProjectionMatrix() {
			return m_Projection; 
		}
		const mat4& GetViewProjectionMatrix() ;
	private:
		void RecalculateView();
	private:
		mat4 m_Projection;
		mat4 m_View;
		mat4 m_ViewProjection;

		vec3 m_Position = { 0.f, 0.f, 0.f };
		float m_Rotation = 0.f;

		bool m_ViewHadChanged = false;
	};

}
