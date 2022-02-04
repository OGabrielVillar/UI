#pragma once
#include <type_traits>

namespace Hazel {

#define  BIT8(x) 1Ui8  << x
#define BIT16(x) 1Ui16 << x
#define BIT32(x) 1Ui32 << x
#define BIT64(x) 1Ui64 << x

	template <
		typename T,
		typename = typename std::enable_if<std::is_enum<T>::value&& std::is_integral<std::underlying_type_t<T>>::value, T>::type, // must be integer
		typename Ty = std::underlying_type_t<T>
	>
	class Flags {
	 public:
		Flags() = default;
		Flags(const T flag_in) : value((Ty)flag_in) {}

		bool operator == (const Flags<T>& rh) {
			return value == rh.value;
		}
		bool operator != (const Flags<T>& rh) {
			return value != rh.value;
		}

		void SetTo(const T rh) {
			value = (Ty)rh;
		}

		void Add(const T rh) {
			value |= (Ty)rh;
		}

		void Remove(const T rh) {
			value ^= (Ty)rh;
		}

		bool Contains(const T rh) {
			return ((value & (Ty)rh) == (Ty)rh);
		}
		bool Contains(const Flags<T> rh) {
			return ((value & rh.value) == (Ty)rh);
		}

		bool NotContains(const T rh) {
			return ((value & (Ty)rh) == Ty(0));
		}
		bool NotContains(const Flags<T> rh) {
			return ((value & rh.value) == Ty(0));
		}

	 private:
		Ty value = (Ty)0;
		//size_t size = sizeof(Ty);
	};

	template <
		typename T,
		typename = typename std::enable_if<std::is_enum<T>::value&& std::is_integral<std::underlying_type_t<T>>::value, T>::type, // must be integer
		typename Ty = std::underlying_type_t<T>
	>
	inline const T operator | (const T a, const T b) {
		return (T)(*(Ty*)&a | *(Ty*)&b);
	}

}
