#pragma once

namespace Hazel::Math {

	class Random {
	 private:
		Random() 
		  : m_Engine64(m_RandomDevice()),
			m_Engine32(m_RandomDevice())
		{ 
			srand (static_cast <unsigned> (time(NULL)));
		}
	 public:
	 	Random(const Random&) = delete;
	 	Random& operator=(const Random&) = delete;

	 public:
	 	inline static float Float() {
	 		return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	 	}
	 	inline static uint64_t uLong() {
	 		return inst.m_UniformDistribution64(inst.m_Engine64);
	 	}
	 	inline static uint32_t uInt() {
	 		return inst.m_UniformDistribution32(inst.m_Engine32);
	 	}
	 private:
		static Random inst;
		std::random_device m_RandomDevice;
		std::mt19937_64 m_Engine64;
	 	std::uniform_int_distribution<std::mt19937_64::result_type> m_UniformDistribution64;
		std::mt19937 m_Engine32;
	 	std::uniform_int_distribution<std::mt19937::result_type> m_UniformDistribution32;
	};

}

namespace Hazel::Math {

	inline static glm::vec3 random_vec3() {
		return glm::vec3(Random::Float(),Random::Float(),Random::Float());
	}

}
