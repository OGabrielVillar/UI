#pragma once

#include "Project/Scene.h"
#include "Project/Entity.h"

namespace Hazel {

	class UILayer {
	public:
		UILayer(entt::registry& registry, const Ref<Canvas>& canvas)
			: m_Canvas(canvas),
			  m_Tree(entt::null),
			  m_Registry(registry)
		{}

		Entity NewFrame(const vec2& position, const vec2& size);

		void Close();

		inline Tree<entt::entity>& GetTree() { return m_Tree; }
		inline entt::registry& GetRegistry() { return m_Registry; }
		inline Ref<Canvas> GetCanvas() const { return Ref<Canvas>(m_Canvas); }

	protected:
		Ref<Canvas> m_Canvas = nullptr;

		Tree<entt::entity> m_Tree;
		entt::registry& m_Registry;
		entt::entity m_WorkingEntity = entt::null;

		entt::entity m_History[90] {entt::null};
		int m_HistoryIndex = 0;
	};



	struct UILayerComponent : public UILayer {
		UILayerComponent(entt::registry& registry, const Ref<Canvas>& canvas)
			: UILayer(registry, canvas)
		{}

		const UILayerComponent(const UILayerComponent& other) 
			: UILayer(other.m_Registry, other.GetCanvas())
		{}

		UILayerComponent& operator=(const UILayerComponent& other)
		{
			return *this;
		}
	};

}
