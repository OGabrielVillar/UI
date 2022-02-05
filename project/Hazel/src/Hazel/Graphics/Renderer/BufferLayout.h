#pragma once

#include "pch.h"

namespace Hazel {
	
	// ----------------------------
	// --- BufferLayoutDataType ---
	// ----------------------------

	enum class BufferLayoutDataType : uint8_t {
		None = 0,
		Bool,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat3, Mat4
	};

	inline std::pair<uint32_t,uint32_t> SizeCountOf(BufferLayoutDataType type) {
		switch (type)
		{
		case Hazel::BufferLayoutDataType::Bool:		  return {1        , 1    };
		case Hazel::BufferLayoutDataType::Float:	  return {4		   , 1    };
		case Hazel::BufferLayoutDataType::Float2:	  return {4 * 2	   , 2    };
		case Hazel::BufferLayoutDataType::Float3:	  return {4 * 3	   , 3    };
		case Hazel::BufferLayoutDataType::Float4:	  return {4 * 4	   , 4    };
		case Hazel::BufferLayoutDataType::Int:		  return {4		   , 1    };
		case Hazel::BufferLayoutDataType::Int2:		  return {4 * 2	   , 2    };
		case Hazel::BufferLayoutDataType::Int3:		  return {4 * 3	   , 3    };
		case Hazel::BufferLayoutDataType::Int4:		  return {4 * 4	   , 4    };
		case Hazel::BufferLayoutDataType::Mat3:		  return {4 * 3 * 3, 3 * 3};
		case Hazel::BufferLayoutDataType::Mat4:		  return {4 * 4 * 4, 4 * 4};
		}
		HZ_ASSERT(false,"[Hazel::SizeCountOf] Unsupported \"BufferLayoutDataType\" case!")
	}

	// ---------------------------
	// --- BufferLayoutElement ---
	// ---------------------------

	struct BufferLayoutElement {
		std::string Name;
		BufferLayoutDataType Type;
		uint32_t Size;
		uint32_t Count;
		uint32_t Offset;
		bool Normalized;

		BufferLayoutElement() = default;
		BufferLayoutElement(BufferLayoutDataType type, const std::string& name, bool normalized = false) 
			: Name(name), Type(type), Offset(0), Normalized(normalized)
		{
			auto SizeCount = SizeCountOf(type);
			Size = SizeCount.first;
			Count = SizeCount.second;
		}
	};

	// --------------------
	// --- BufferLayout ---
	// --------------------

	class BufferLayout {
	 public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferLayoutElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetAndStride();
		}
		//template<typename >
		//BufferLayout(const std::initializer_list<BufferLayoutElement>& elements)
		//	: m_Elements(elements)
		//{
		//	CalculateOffsetAndStride();
		//}

		inline const std::vector<BufferLayoutElement>& GetElements() const { return m_Elements; };
		inline uint32_t GetStride() const { return m_Stride; }

		using Iterator = std::vector<BufferLayoutElement>::iterator;
		using ConstIterator = std::vector<BufferLayoutElement>::const_iterator;
		Iterator begin() { return m_Elements.begin(); }
		Iterator end() { return m_Elements.end(); }
		ConstIterator begin() const { return m_Elements.begin(); }
		ConstIterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetAndStride() {
			m_Stride = 0;
			uint32_t offset(0);
			for (auto& element : m_Elements) {
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

	 private:
		std::vector<BufferLayoutElement> m_Elements;
		uint32_t m_Stride = 0;
	};

}
