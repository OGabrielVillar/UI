#pragma once
//
//#include "Hazel/Renderer/Texture.h"
//#include "Hazel/Renderer/Renderer2D.h"
//#include "Hazel/Renderer/RenderCommandBuffer.h"
//#include "Hazel/Renderer/SceneRenderer.h"
//
//
//#include "Hazel/UI/UIElement.h"
//
//#include <entt/entt.hpp>
//
//namespace Hazel::UI {
//
//	class UILayer {
//	 public:
//		UILayer(const std::string& name = "UILayer");
//		virtual ~UILayer() = default;
//		UILayer(const UILayer&) = default;
//
//		void OnAttach() {}
//		void OnDetach() {}
//		void OnUpdate(Timestep ts);
//		void OnEvent(Event& event);
//
//		UI::Element& CreateElement(const std::string& name);
//
//	 private:
//		entt::registry m_registry;
//		entt::entity screen_element = entt::null;
//		entt::entity testFrame = entt::null;
//
//		float m_LineWidth = 2.0f;
//		EditorCamera m_UICamera;
//		Ref<Scene> m_UIScene;
//		Ref<SceneRenderer> m_UIRenderer;
//		Ref<Renderer2D> m_UIRenderer2D;
//	};
//
//}
