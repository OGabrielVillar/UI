#pragma once

#include "pch.h"
#include "Run/Log.h"

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
		union {
			uint32_t Size;
			std::pair<uint32_t,uint32_t> SizeCount;
		};
		uint32_t& Count = SizeCount.second;
		uint32_t Offset;
		bool Normalized;

		BufferLayoutElement() {}
		BufferLayoutElement(BufferLayoutDataType type, const std::string& name, bool normalized = false) 
			: Name(name), Type(type), SizeCount(SizeCountOf(type)), Offset(0), Normalized(normalized)
		{}
	};

	// --------------------
	// --- BufferLayout ---
	// --------------------

	class BufferLayout {
	 public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferLayoutElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetAndStride();
		}

		inline const std::vector<BufferLayoutElement>& GetElements() const { return m_Elements; };

		using Iterator = std::vector<BufferLayoutElement>::iterator;
		Iterator begin() { return m_Elements.begin(); }
		Iterator end() { return m_Elements.end(); }
		uint32_t GetStride() const { return m_Stride; }

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
		uint32_t m_Stride;
	};

}
