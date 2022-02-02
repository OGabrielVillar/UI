#pragma once

#include "core.h"

namespace Hazel {



	using AudioBuffer_44100Hz_16bits = Buffer<44100,int16_t>;
	using AudioBuffer_44100Hz_24bits = Buffer<44100,int24_t>;
	using AudioBuffer_44100Hz_32bits = Buffer<44100,int32_t>;

	template<typename package>
	class Signal {
		template<typename ... Args>
		Signal(Args ... args)
			: m_pack(std::forward<Args>(args ...))
		{}
		package m_pack;
	};

}
