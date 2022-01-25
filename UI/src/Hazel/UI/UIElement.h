#pragma once

#include "Hazel/UI/UIComponent.h"

#include <entt/entt.hpp>

namespace Hazel::UI {

	class Element 
	{
	 public:
		Element() = default;
		Element(entt::entity handle, entt::registry& registry)
			: m_EntityHandle(handle), m_Registry(registry) {}
		~Element() {}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			HZ_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			return m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}
		template<typename T>
		bool HasComponent()
		{
			//return m_Registry.has<T>(m_EntityHandle);
		}

		operator uint32_t () const { return (uint32_t)m_EntityHandle; }
		operator entt::entity() const { return m_EntityHandle; }
		operator bool() const { return (m_EntityHandle != entt::null); }

	 protected:
		 entt::entity m_EntityHandle;
		 entt::registry& m_Registry;
	};



	class Button : public Element 
	{
	 public:
		Button() = default;
		Button(const Element& in)
			: Element(in)
		{}
		Button(entt::entity handle, entt::registry & registry)
			: Element(handle, registry)
		{}
	};

	class Frame : public Element
	{
	public:
		Frame() = default;
		Frame(const Element& in)
			: Element(in)
		{}
		Frame(entt::entity handle, entt::registry& registry)
			: Element(handle, registry)
		{}
	};

}
