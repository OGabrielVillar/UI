#pragma once

#include "Entity.h"

namespace Hazel {

	class Hierarchy {

		using vecIterator = std::vector<entt::entity>::iterator;

	private:
		class ReversedHierarchy {
		public:
			ReversedHierarchy() = delete;

			std::vector<entt::entity>::reverse_iterator begin()
			{
				return m_Childs.rbegin();
			}

			std::vector<entt::entity>::reverse_iterator end()
			{
				return m_Childs.rend();
			}
		private:
			entt::entity m_Parent = entt::null;
			std::vector<entt::entity> m_Childs;
		};

	public:
		Hierarchy(const Ref<entt::registry>& registry, entt::entity id, Hierarchy& parent);
		Hierarchy(const Ref<entt::registry>& registry, entt::entity id);
		Hierarchy(const Ref<entt::registry>& registry);

		void SetParent(Hierarchy& parent);

		Ref<entt::registry>& GetRegistry();

		void AddChilds(std::initializer_list<entt::entity> childs);

		entt::entity AddChild(entt::entity child);

		// Returns true if it was a valid child to remove.
		bool RemoveChild(entt::entity child);

		bool Swap(entt::entity entity_a, entt::entity entity_b);

		bool MoveOver(entt::entity move_entity, entt::entity over_entity);

		bool MoveUnder(entt::entity move_entity, entt::entity under_entity);

		void TopToBottom(const std::function<void(Entity)>& function);

		//template<typename ... COMPONENT>
		//void TopToBottomComponent(const std::function<void(COMPONENT&...)>& function)
		//{
		//	for ( auto iterator = m_Childs.rbegin(); iterator != m_Childs.rend(); iterator++)
		//	{
		//		auto child = *iterator;
		//
		//		if (m_Registry->all_of<HierarchyComponent, COMPONENT...>(child))
		//			m_Registry->get<HierarchyComponent>(child).TopToBottomComponent<COMPONENT...>(function);
		//	}
		//	if (m_Registry->all_of<COMPONENT...>(m_ID))
		//		function(m_Registry->get<COMPONENT...>(m_ID));
		//}

		void BottomToTop(const std::function<void(Entity)>& function);

		template<typename COMPONENT>
		COMPONENT* GetParent() const
		{
			if(m_Parent != entt::null)
				if (m_Registry->any_of<COMPONENT>(m_Parent))
					return &m_Registry->get<COMPONENT>(m_Parent);
			return nullptr;
		}

	public:
		vecIterator begin()
		{
			return m_Childs.begin();
		}

		vecIterator end()
		{
			return m_Childs.end();
		}

		ReversedHierarchy& reversed()
		{
			return *((ReversedHierarchy*)this);
		}

	private:
		Ref<entt::registry> m_Registry;
		entt::entity m_ID = entt::null;
		entt::entity m_Parent = entt::null;
		std::vector<entt::entity> m_Childs;
	};

}
