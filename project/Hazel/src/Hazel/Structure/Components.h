#pragma once

#include "Information.h"
#include "Hierarchy.h"
#include "Transform.h"

#include "Input/CommandCard.h"

#include "Graphics/Material.h"

#include "Structure/Camera.h"
#include "Structure/Canvas.h"

namespace Hazel::Component {
	
	template<typename ... Ts>
	struct Requires { };
	
	template<typename ... Ts>
	struct Exclude { };

	template <class T, class Enable = void>
	struct has_requirement
	{
		static constexpr bool value = false;
	};
	
	template <class T>
	struct has_requirement<T, std::enable_if_t<(sizeof(T::Requirement) > 0)>>
	{
		static constexpr bool value = true;
	};

	template <class T, class Enable = void>
	struct has_exclusion
	{
		static constexpr bool value = false;
	};
	
	template <class T>
	struct has_exclusion<T, std::enable_if_t<(sizeof(T::Exclusion) > 0)>>
	{
		static constexpr bool value = true;
	};

}

namespace Hazel {
#define REQUIRES(...) inline static Component::Requires<__VA_ARGS__> Requirement
#define EXCLUDE(...) inline static Component::Exclude<__VA_ARGS__> Exclusion
}

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

}
