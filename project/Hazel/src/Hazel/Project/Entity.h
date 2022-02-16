#pragma once

#include "Component/Transform.h"
#include "Component/Camera.h"

#include "entt/entt.hpp"

#include "Component/InformationComponent.h"

namespace Hazel {

	class Entity {
	public:
		Entity(entt::registry& registry)
		  : m_ID(registry.create()),
			m_Registry(registry)
		{}

		template<typename COMPONENT, typename ... Args>
		void AddComponent(Args&&... args)
		{
			m_Registry.emplace<COMPONENT>(m_ID, std::forward<Args>(args)...);
		}

	private:
		entt::entity m_ID;
		entt::registry& m_Registry;
	};

	class Camera : public Entity 
	{
	public:
		Camera(entt::registry& registry, const vec2& aspectRatio);
		
		inline void SetAspectRatio(const vec2& aspectRatio){ m_CameraComponent.SetAspectRatio(aspectRatio); }
		inline const mat4& GetViewProjectionMatrix() { return m_CameraComponent.GetViewProjectionMatrix(); }

		inline TransformComponent& GetTransform() { return m_TransformComponent; }
		//inline CameraComponent& GetCamera() { return m_CameraComponent; }
	private:
		TransformComponent m_TransformComponent;
		CameraComponent m_CameraComponent;
	};

}
