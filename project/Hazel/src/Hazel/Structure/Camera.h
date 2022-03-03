#pragma once

namespace Hazel
{

	struct Camera {
	 public:
		Camera(const vec2& aspectRatio, const Ref<const mat4> transform);

		void SetAspectRatio(const vec2& aspectRatio);

		inline const mat4& GetViewMatrix(){
			RecalculateView();
			return m_View; 
		}
		inline const mat4& GetProjectionMatrix() {
			return m_Projection; 
		}
		const mat4& GetViewProjectionMatrix();

	 private:
		void RecalculateView();

	 private:
		mat4 m_Projection;
		mat4 m_View;
		mat4 m_ViewProjection;

		//vec2 m_AspectRatio;
		Ref<const mat4> m_Transform;

		bool m_ViewHadChanged = false;
	};

}
