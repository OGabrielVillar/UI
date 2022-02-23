#pragma once

namespace Hazel {

	template<typename ... Args>
	static constexpr uint32_t lengthof(Args ... args)
	{ 
		return (strlen(args) + ... + 0);
	}

	class SliderEnumeration {
	private:

	public:
		template<typename ... Args>
		constexpr SliderEnumeration(Args&& ... enums)
		  : m_Size(sizeof...(Args)),
			m_Length(lengthof(enums ...) + m_Size),
			m_Data(new char[m_Size + m_Length]{})
		{
			static_assert(sizeof...(Args) != 0, "SliderEnumeration: cannot take 0 arguments!"); 

			uint16_t shift = 0;

			uint16_t count = 0;

			char x[sizeof...(Args)] = { pushStr(enums, shift, count)... };
		}

		char pushStr(const char* str, uint16_t& shift, uint16_t& count) 
		{ 
			m_Data[count] = (char)shift;

			const size_t len(strlen(str) + 1);
			const size_t str_begin = m_Size + shift;

			for (size_t i = 0; i < len; i++)
				m_Data[str_begin + i] = str[i];

			shift += (uint16_t)len;

			count++;

			return 0; 
		}

		const char* operator[](uint16_t index) const 
		{
			uint16_t cap = index % m_Size;
			return &m_Data[m_Size + m_Data[cap]]; 
		}
		int length() const { return m_Size + m_Length ; }

	private:
		const uint8_t m_Size;
		const uint16_t m_Length;
		char* m_Data;
	};

}
