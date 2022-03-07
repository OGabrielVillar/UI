#pragma once

#include "Structure/Entity.h"
#include "Layout.h"
#include "Input/Event.h"
#include "Run/Window.h"

namespace Hazel {

	class UILayer {

	public:
		UILayer(const Ref<entt::registry>& registry, entt::entity id);

		Entity NewSpace(const std::string& name);
		Entity NewFrame(const std::string& name);
		Entity NewViewport(const std::string& name);
		Entity NewDockingSpace(const std::string& name);

		void SetSize(const vec2& size);
		void SetPosition(const vec2& position);
		void SetAnchor(Anchor anchor);
		void SetEdgeSnap(EdgeSnap edgeSnap);
		void SetWindowHandlePosition(Window& window);
		MaterialComponent& GetMaterial();

		bool OnClick();
		bool OnClickRelease();
		bool OnRightClick();
		bool OnCursorMovement(const EventCursorPosition* event);
		bool OnDrag();

		void Close();

		inline Ref<entt::registry>& GetRegistry() { return m_Registry; }
		HierarchyComponent& GetHierarchy();

	private:
		Entity NewElement(const std::string& name);

	protected:
		entt::entity m_ID = entt::null;
		Ref<entt::registry> m_Registry;

		entt::entity m_WorkingEntity = entt::null;
		entt::entity m_History[90] {entt::null};
		int m_HistoryIndex = 0;

	private:
		entt::entity m_DraggingID = entt::null;
		vec2int m_CursorPosition = { 0,0 };
		bool m_IsDragging = false;
	};



}
