#pragma once

#include "Structure/Entity.h"

namespace Hazel {

	class UILayer {

	public:
		UILayer(const Ref<entt::registry>& registry, entt::entity id)
		  : m_ID(id),
			m_Registry(registry)
		{}

		Entity NewFrame(const std::string& name);
		Entity NewViewport(const std::string& name);

		void SetSize(const vec2& size);
		void SetPosition(const vec2& position);
		void SetAnchor(Anchor anchor);
		void SetSnap(Snap snap);
		MaterialComponent& GetMaterial();

		void Close();

		inline Ref<entt::registry>& GetRegistry() { return m_Registry; }
		inline HierarchyComponent& GetHierarchy() { return m_Registry->get<HierarchyComponent>(m_ID); }

	private:
		Entity NewElement(const std::string& name);

	protected:
		entt::entity m_ID = entt::null;
		Ref<entt::registry> m_Registry;

		entt::entity m_WorkingEntity = entt::null;
		entt::entity m_History[90] {entt::null};
		int m_HistoryIndex = 0;
	};



	struct UILayerComponent : public UILayer {
		UILayerComponent(Ref<entt::registry>& registry, entt::entity id)
			: UILayer(registry, id)
		{}

		const UILayerComponent(const UILayerComponent& other) 
			: UILayer(other.m_Registry, other.m_ID)
		{}

		UILayerComponent& operator=(const UILayerComponent& other)
		{
			return *this;
		}
	};

}
