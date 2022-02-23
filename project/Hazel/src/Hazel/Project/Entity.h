#pragma once

#include "Component/Component.h"

#include "Component/TransformComponent.h"
#include "Component/CameraComponent.h"
#include "Component/CommandCardComponent.h"
#include "Component/InformationComponent.h"

namespace Hazel {

	class Entity {
	private:
		template<typename ... Ts>
		inline bool _MatchesRequirements(Component::Requires<Ts ...> requirements)
		{ 
			return m_Registry.all_of<Ts ...>(m_ID); 
		}
		template<typename COMPONENT>
		inline bool MatchesRequirements()
		{ 
			return _MatchesRequirements(COMPONENT::Requirement); 
		}
		template<typename ... Ts>
		inline bool _MatchesExclusions(Component::Exclude<Ts ...> exclusions)
		{ 
			return !(m_Registry.any_of<Ts ...>(m_ID));
		}
		template<typename COMPONENT>
		inline bool MatchesExclusions()
		{ 
			return _MatchesExclusions(COMPONENT::Exclusion); 
		}

	public:
		Entity(entt::registry& registry)
		  : m_ID(registry.create()),
			m_Registry(registry)
		{}

		template<typename COMPONENT, typename ... Args>
		inline COMPONENT* AddComponent(Args&&... args)
		{
			bool matchesConditions = true;
			if constexpr ( Component::has_requirement<COMPONENT>::value ) 
				if (!MatchesRequirements<COMPONENT>()) 
				{
					matchesConditions = false;
					HZ_ASSERT(false, "Component don't match requirements!"); // TODO Create lacking components.
				}
			if constexpr ( Component::has_exclusion<COMPONENT>::value ) 
				if (!MatchesExclusions<COMPONENT>()) 
				{
					matchesConditions = false;
					HZ_ASSERT(false, "Component don't match exclusions!"); // TODO smarter way to address that problem.
				}
			if(matchesConditions)
				return &m_Registry.emplace<COMPONENT>(m_ID, std::forward<Args>(args)...);
			return nullptr;
		}

		template<typename COMPONENT>
		inline COMPONENT* GetComponent()
		{
			COMPONENT* result = nullptr;
			if ( m_Registry.any_of<COMPONENT>(m_ID) )
				result = &m_Registry.get<COMPONENT>(m_ID);
			return result;
		}

		inline entt::entity Raw() const { return m_ID; }

	protected:
		entt::entity m_ID;
		entt::registry& m_Registry;
	};

	class CameraEntity : public Entity 
	{
	public:
		CameraEntity(entt::registry& registry, const vec2& aspectRatio);
		
		inline void SetAspectRatio(const vec2& aspectRatio){ GetCamera().SetAspectRatio(aspectRatio); }
		inline const mat4& GetViewProjectionMatrix() { return GetCamera().GetViewProjectionMatrix(); }

		inline TransformComponent& GetTransform() { return m_Registry.get<TransformComponent>(m_ID); }
		inline CameraComponent& GetCamera() { return m_Registry.get<CameraComponent>(m_ID); }
	};

}
