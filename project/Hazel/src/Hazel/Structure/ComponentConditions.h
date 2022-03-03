#pragma once

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
