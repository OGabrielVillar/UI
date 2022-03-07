#pragma once

#include "ComponentConditions.h"

#include "Information.h"
#include "Hierarchy.h"
#include "Transform.h"

#include "Input/CommandCard.h"

#include "Graphics/Material.h"

#include "Structure/Camera.h"
#include "Structure/Canvas.h"

#include "UI/WindowHandle.h"
#include "UI/Viewport.h"
#include "UI/UILayer.h"

namespace Hazel
{

	struct InformationComponent : public Information {
	 public:
		InformationComponent(const std::string& name, UUID::Type type = UUID::Type::Asset)
		  : Information(name, type)
		{}
	};

	struct TransformComponent : public Transform {
	 public:
		TransformComponent()
		  : Transform()
		{}
	};

	struct MaterialComponent : public Material {
	 public:
		MaterialComponent() = default;
	};

	struct CommandCardComponent : public CommandCard {
	 public:
		CommandCardComponent()
		  : CommandCard()
		{}
	};

	struct CameraComponent : public Camera {
	 public:
		CameraComponent(const vec2& aspectRatio, const Ref<const mat4> transform)
		  : Camera(aspectRatio, transform)
		{}

		REQUIRES(TransformComponent);
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

	struct HierarchyComponent : public Hierarchy {
	 public:
		HierarchyComponent(const Ref<entt::registry>& registry, entt::entity id, Hierarchy& parent)
		  : Hierarchy(registry, id, parent)
		{}
		HierarchyComponent(const Ref<entt::registry>& registry, entt::entity id)
		  : Hierarchy(registry, id)
		{}
		HierarchyComponent(const Ref<entt::registry>& registry)
		  : Hierarchy(registry)
		{}
		HierarchyComponent& operator =(const HierarchyComponent&) 
		{ return *this; }
	};

	struct ViewportComponent : public Viewport {
	public:
		ViewportComponent() {}

		REQUIRES(LayoutComponent);
	};

	struct WindowHandleComponent : public WindowHandle {
	public:
		WindowHandleComponent( Window& window ) 
			: WindowHandle(window)
		{}

		REQUIRES(LayoutComponent);
	};

}
