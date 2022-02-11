#pragma once
#include <type_traits>

namespace Hazel {

#define  BIT8(x) 1Ui8  << x
#define BIT16(x) 1Ui16 << x
#define BIT32(x) 1Ui32 << x
#define BIT64(x) 1Ui64 << x

	template <
		typename T,
		T DefaultValue = (T)0,
		typename = typename std::enable_if<std::is_enum<T>::value&& std::is_integral<std::underlying_type_t<T>>::value, T>::type, // must be integer
		typename Ty = std::underlying_type_t<T>
	>
	class Flags {
	 public:
		Flags() : value((Ty)DefaultValue) {}
		Flags(T flag_in) : value((Ty)flag_in) {}
		Flags(Ty value_in) : value(value_in) {}
		
		template <typename T2>
		inline operator Flags<T2>() {
			Flags<T2> other;
			other.value = value;
			return other;
		}

		template <typename T2>
		inline operator Flags<T2>&() {
			return *((Flags<T2>*)this);
		}

		inline bool operator == (const Flags<T>& rh) const {
			return value == rh.value;
		}
		inline bool operator != (const Flags<T>& rh) const {
			return value != rh.value;
		}

		inline void SetTo(const T rh) {
			value = (Ty)rh;
		}

		inline void Add(const T rh) {
			value |= (Ty)rh;
		}

		inline void Remove(const T rh) {
			value ^= (Ty)rh;
		}

		inline bool Contains(const T rh) const {
			return ((value & (Ty)rh) == (Ty)rh);
		}
		inline bool Contains(const Flags<T> rh) const {
			return ((value & rh.value) == (Ty)rh);
		}

		inline bool NotContains(const T rh) const {
			return ((value & (Ty)rh) == Ty(0));
		}
		inline bool NotContains(const Flags<T> rh) const {
			return ((value & rh.value) == Ty(0));
		}

	 private:
		Ty value = (Ty)0;
	};

	template <
		typename T,
		typename = typename std::enable_if<std::is_enum<T>::value&& std::is_integral<std::underlying_type_t<T>>::value, T>::type, // must be integer
		typename Ty = std::underlying_type_t<T>
	>
	inline constexpr const T operator | (const T a, const T b) {
		//return (T)(*(Ty*)&a | *(Ty*)&b);
		return (T)((Ty)a | (Ty)b);
	}

}
