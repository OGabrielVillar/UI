#pragma once
#include "pch.h"

namespace Hazel::Math::_internals {

	class _Random {
	 private:
		_Random() { 
			m_randomEngine.seed(std::random_device()());
			srand (static_cast <unsigned> (time(NULL)));
		}
	 public:
	 	_Random(const _Random&) = delete;
	 	_Random& operator=(const _Random&) = delete;

	 public:
	 	inline float Float() {
	 		return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	 	}
		inline static _Random& get_instance(){ return inst; }
	 private:
		static _Random inst;
	 	std::mt19937 m_randomEngine;
	 	std::uniform_int_distribution<std::mt19937::result_type> m_distribution;

	};
}

namespace Hazel::Math {

	inline static float random_float() {
		//using namespace internals::_Random;
		//return get_instance().Float();
	}

	inline static float random_normalized_float() { 
		return _internals::_Random::get_instance().Float(); 
	}

	inline static glm::vec3 random_vec3() {
		return glm::vec3(random_normalized_float(),random_normalized_float(),random_normalized_float());
	}

}
