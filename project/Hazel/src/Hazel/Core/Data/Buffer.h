#pragma once

namespace Hazel::Data {

	template<uint32_t _size, typename T>
	struct Buffer {
		Buffer() = default;
		template<typename... Args>
		Buffer(Args ... args)
			: m_pack { std::forward<Args>(args) ... }
		{}

		T& operator [](uint32_t index){
			if (index >= _size)
				return m_pack[0];
			return m_pack[index];
		}

		T* begin() {
			return m_pack;
		}
		T* end() {
			return m_pack + _size;
		}

		T m_pack[_size];
	};

}
