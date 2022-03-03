#pragma once

#include "ComponentConditions.h"

namespace Hazel {
	
	struct TransformComponent;
	struct CameraComponent;
	struct HierarchyComponent;
	struct MaterialComponent;

	class Entity {
	private:
		template<typename ... Ts>
		inline bool _MatchesRequirements(Component::Requires<Ts ...> requirements)
		{ 
			return m_Registry->all_of<Ts ...>(m_ID); 
		}
		template<typename COMPONENT>
		inline bool MatchesRequirements()
		{ 
			return _MatchesRequirements(COMPONENT::Requirement); 
		}
		template<typename ... Ts>
		inline bool _MatchesExclusions(Component::Exclude<Ts ...> exclusions)
		{ 
			return !(m_Registry->any_of<Ts ...>(m_ID));
		}
		template<typename COMPONENT>
		inline bool MatchesExclusions()
		{ 
			return _MatchesExclusions(COMPONENT::Exclusion); 
		}

	public:
		Entity();
		Entity(Ref<entt::registry>& registry);
		Entity(Ref<entt::registry>& registry, entt::entity id);
		Entity(Ref<entt::registry>& registry, const std::string& name);

		Entity(const Entity& other);
		Entity& operator=(const Entity& other);

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
				return &m_Registry->emplace<COMPONENT>(m_ID, std::forward<Args>(args)...);
			return nullptr;
		}

		template<typename COMPONENT>
		inline COMPONENT& GetComponent()
		{
			return m_Registry->get<COMPONENT>(m_ID);
		}
		
		template<typename... COMPONENTS>
		inline bool HaveComponent() 
		{
			return m_Registry->all_of<COMPONENTS...>(m_ID);
		}

		inline entt::entity Raw() const { return m_ID; }

	protected:
		entt::entity m_ID;
		Ref<entt::registry> m_Registry;
	};

	class CameraEntity : public Entity 
	{
	public:
		CameraEntity(Ref<entt::registry>& registry, const vec2& aspectRatio);
		
		void SetAspectRatio(const vec2& aspectRatio);
		const mat4& GetViewProjectionMatrix();

		TransformComponent& GetTransform();
		CameraComponent& GetCamera();
	};

}
