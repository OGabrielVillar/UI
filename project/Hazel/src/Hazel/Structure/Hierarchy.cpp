#include "pch.h"
#include "Hierarchy.h"
#include "Structure/Entity.h"
#include "Structure/Components.h"

namespace Hazel {

	Hierarchy::Hierarchy(const Ref<entt::registry>& registry, entt::entity id, Hierarchy& parent)
	  : m_Registry(registry),
		m_ID(id),
		m_Parent(parent.m_ID)
	{
		if (m_Parent != entt::null)
			m_Registry->get<HierarchyComponent>(m_Parent).RemoveChild(m_ID);

		parent.AddChild(m_ID);
	}

	Hierarchy::Hierarchy(const Ref<entt::registry>& registry, entt::entity id)
	  : m_Registry(registry),
		m_ID(id)
	{}

	Hierarchy::Hierarchy(const Ref<entt::registry>& registry)
		: m_Registry(registry)
	{}

	void Hierarchy::SetParent(Hierarchy& parent)
	{
		m_Parent = parent.m_ID;

		if (m_Parent != entt::null)
			m_Registry->get<HierarchyComponent>(m_Parent).RemoveChild(m_ID);

		parent.AddChild(m_ID);
	}

	Ref<entt::registry>& Hierarchy::GetRegistry()
	{
		return m_Registry;
	}

	void Hierarchy::AddChilds(std::initializer_list<entt::entity> childs)
	{
		m_Childs.insert(m_Childs.end(), childs);
	}

	entt::entity Hierarchy::AddChild(entt::entity child)
	{
		m_Childs.push_back(child);
		return m_Childs.back();
	}

	bool Hierarchy::RemoveChild(entt::entity child)
	{
		for (auto iterator = m_Childs.begin(); iterator != m_Childs.end(); iterator++)
		{
			if(*iterator == child) {
				m_Childs.erase(iterator);
				return true;
			}
		}
		return false;
	}

	bool Hierarchy::Swap(entt::entity entity_a, entt::entity entity_b)
	{
		entt::entity* found_a = nullptr;
		entt::entity* found_b = nullptr;

		for ( auto& entity : m_Childs)
		{
			if(entity == entity_a)
				found_a = &entity;

			if(entity == entity_b)
				found_b = &entity;

			if(found_a && found_b) {
				std::swap(*found_a, *found_b);
				return true;
			}
		}
		return false;
	}

	bool Hierarchy::MoveOver(entt::entity move_entity, entt::entity over_entity)
	{
		entt::entity move = entt::null;
		int index = 0;

		for (auto iterator = m_Childs.begin(); iterator != m_Childs.end(); iterator++)
		{
			auto& entity = *iterator;

			//If finds Move first;
			if(entity == move_entity) {

				move = entity;

				m_Childs.erase(iterator);

				for (auto next_iterator = m_Childs.begin() + index; next_iterator != m_Childs.end(); next_iterator++)
				{
					if(*next_iterator == over_entity) {
						m_Childs.insert(next_iterator +1, move);
						return true;
					}
				}

				return false;

			}
			
			//If finds Under first;
			if(entity == over_entity) {

				int over_index = index;
				
				for (auto next_iterator = m_Childs.begin() + index + 1; next_iterator != m_Childs.end(); next_iterator++)
				{
					if(*next_iterator == move_entity) {
						move = *next_iterator;
						m_Childs.erase(next_iterator);
						m_Childs.insert(m_Childs.begin() + over_index +1, move);
						return true;
					}
				}

				return false;
			}

			index++;
		}
		return false;
	}

	bool Hierarchy::MoveUnder(entt::entity move_entity, entt::entity under_entity)
	{
		entt::entity move = entt::null;
		int index = 0;

		for (auto iterator = m_Childs.begin(); iterator != m_Childs.end(); iterator++)
		{
			auto& entity = *iterator;

			//If finds Move first;
			if(entity == move_entity) {

				move = entity;

				m_Childs.erase(iterator);

				for (auto next_iterator = m_Childs.begin() + index; next_iterator != m_Childs.end(); next_iterator++)
				{
					if(*next_iterator == under_entity) {
						m_Childs.insert(next_iterator, move);
						return true;
					}
				}

				return false;

			}
			
			//If finds Under first;
			if(entity == under_entity) {
				
				int under_index = index;
				
				for (auto next_iterator = m_Childs.begin() + index + 1; next_iterator != m_Childs.end(); next_iterator++)
				{
					if(*next_iterator == move_entity) {
						move = *next_iterator;
						m_Childs.erase(next_iterator);
						m_Childs.insert(m_Childs.begin() + under_index, move);
						return true;
					}
				}

				return false;
			}

			index++;
		}
		return false;
	}

	void Hierarchy::TopToBottom(const std::function<void(const Entity&)>& function)
	{
		for ( auto iterator = m_Childs.rbegin(); iterator != m_Childs.rend(); iterator++)
		{
			auto child = *iterator;

			if (m_Registry->any_of<HierarchyComponent>(child))
				m_Registry->get<HierarchyComponent>(child).TopToBottom(function);
		}
		function({m_Registry, m_ID});
	}

	bool Hierarchy::TopToBottomBool(const std::function<bool(const Entity&)>& function)
	{
		for ( auto iterator = m_Childs.rbegin(); iterator != m_Childs.rend(); iterator++)
		{
			auto child = *iterator;

			if (m_Registry->any_of<HierarchyComponent>(child))
				if (m_Registry->get<HierarchyComponent>(child).TopToBottomBool(function)) return true;
		}
		return function({m_Registry, m_ID});
	}

	void Hierarchy::BottomToTop(const std::function<void(const Entity&)>& function)
	{
		function({m_Registry, m_ID});
		for ( auto child : m_Childs )
		{
			if (m_Registry->any_of<HierarchyComponent>(child))
				m_Registry->get<HierarchyComponent>(child).BottomToTop(function);
		}
	}

	bool Hierarchy::BottomToTopBool(const std::function<bool(const Entity&)>& function)
	{
		if (function({m_Registry, m_ID})) return true;
		for ( auto child : m_Childs )
		{
			if (m_Registry->any_of<HierarchyComponent>(child))
				if (m_Registry->get<HierarchyComponent>(child).BottomToTopBool(function)) return true;
		}
		return false;
	}

}
